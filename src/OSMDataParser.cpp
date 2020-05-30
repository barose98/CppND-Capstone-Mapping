/*
 * OSMDataParser.cpp
 *
 *  Created on: May 6, 2020
 *      Author: Barrett Rose
 */

#include "OSMDataParser.h"

OSMDataParser::OSMDataParser(std::shared_ptr<OSMDownloadQueue<std::string>> queue,  std::shared_ptr<OSMDrawingQueue<bool>> draw_queue)
: parser_queue(queue), drawing_queue(draw_queue)
{
//    std::cout <<  "OSM Parser Constructor  " <<this<<std::endl;
    state = new ParserStruct();
}

OSMDataParser::OSMDataParser(const OSMDataParser &other)
{
//    std::cout <<  "OSM Parser Copy Constructor  " <<this<<std::endl;
    this->state =other.state;
    this->parser_queue=other.parser_queue;
    this->drawing_queue=other.drawing_queue;
}

OSMDataParser::OSMDataParser(OSMDataParser &&other)
{
//    std::cout <<  "OSM Parser Move Constructor  " <<this<<std::endl;
    this->state =other.state;
    this->parser_queue=other.parser_queue;
    this->drawing_queue=other.drawing_queue;
}

OSMDataParser OSMDataParser::operator =(const OSMDataParser &other)
{
    std::cout <<  "OSM Parser Copy Assignment Constructor  " <<this<<std::endl;
    this->state =other.state;
    this->parser_queue=other.parser_queue;
    this->drawing_queue=other.drawing_queue;
    return *this;
}

OSMDataParser OSMDataParser::operator =(OSMDataParser &&other)
{
    std::cout <<  "OSM Parser Move Assignment  Constructor  " <<this<<std::endl;
    this->state =other.state;
    this->parser_queue=other.parser_queue;
    this->drawing_queue=other.drawing_queue;
    return *this;
}
OSMDataParser::~OSMDataParser()
{
//    std::cout <<  "OSM Parser Destructor "<<this<<std::endl;
//    if(state !=nullptr)
//        delete state;
}

void OSMDataParser::parseOSMXML(std::shared_ptr<CairoDrawer> drawer, std::stringstream &xml_data){
    auto  startElement = [](void *userData, const XML_Char *name, const XML_Char **attrs)
            {
        struct ParserStruct *state = (struct ParserStruct *) userData;
        state->depth++;
        if(state->depth == 2)
            state->node_name = name;
        if(state->node_name== "node"  ){
            if(state->depth == 2){
                //the actual node
                NodeStruct node;
                node.id = attrs[1];
                node.point.latitude =std::stof(attrs[3]);
                node.point.longitude =std::stof(attrs[5]);
                state->drawer->nodes.emplace_back(node);
//                state->drawer->drawNode(node);
            }else{
                //tags within node
            }
        }else  if(state->node_name== "way"  ){
            if(state->depth == 2){
                //the actual way
//                std::cout << std::endl;
                WayStruct way;
                way.id=attrs[1];
                state->currentWay = way;
                }else if(state->depth == 3){
                    if ( std::string(name)=="nd"){
                        state->currentWay.nds.emplace_back(attrs[1]);

                    }else{
                        if(std::string(attrs[1]) == "waterway"){
                            state->currentWay.waterway = attrs[3];
                        }else if(std::string(attrs[1]) == "highway"){
                            state->currentWay.highway = attrs[3];
                        }else if(std::string(attrs[1]) == "name"){
                            state->currentWay.name = attrs[3];
                        }else if(std::string(attrs[1]) == "building"){
                            state->currentWay.isBuilding = true;
                        }else if(std::string(attrs[3]) == "water"){
                            state->currentWay.isWater= true;
                            state->currentWay.waterway = attrs[1];
                        }
                }
            }
        }

            };

      auto endElement = [](void *userData, const XML_Char *name){
      struct ParserStruct *state = (struct ParserStruct *) userData;
      if ( std::string(name)=="way"){
          state->drawer->ways.emplace_back(state->currentWay);
      }
      state->depth--;
    };

    state->ok =1;
    state->drawer = drawer;

    XML_Parser parser = XML_ParserCreateNS(NULL, '\0');
    XML_SetUserData(parser, state);
    XML_SetElementHandler(parser, startElement, endElement);
    if(state->ok && XML_Parse(parser, xml_data.str().c_str(), xml_data.str().size(), 0) == 0) {
        int error_code = XML_GetErrorCode(parser);
        std::cerr << "ERROR PARSING error_code: "<< error_code<<"-"<<XML_ErrorString(XML_GetErrorCode(parser))   <<std::endl;
    }

    XML_ParserFree(parser);
}

std::string OSMDataParser::receiveOSMXML(std::shared_ptr<CairoDrawer> drawer)
{
    std::cout << "OSM Data Receiving"  <<std::endl;
    parsingStarted  = std::chrono::system_clock::now();
    std::stringstream xml_data;
    do{

        xml_data<< parser_queue->pull() ;
        if(xml_data.str().find("<downloaderError/>") != std::string::npos){
            std::cerr <<  xml_data.str()  <<std::endl;
            xml_data = std::stringstream("");
            break;
        }
    }while( !xml_data.str().empty() && xml_data.str().substr(xml_data.str().length()-7 , 6 )  != "</osm>");
    std::cout << "OSM Data Received"  <<std::endl;
    if(!xml_data.str().empty()){
        std::cout <<  "Parsing" <<std::endl;
        this->parseOSMXML(drawer, xml_data);
        std::cout <<  "Finished Parsing" <<std::endl;
    }
    std::cout <<  "Drawing" <<std::endl;
    std::vector<std::future<bool>>  futures={};
    std::vector<std::thread> threads ={};

    for(WayStruct way : drawer->ways){
        std::promise<bool> promise;
        std::future<bool> result =promise.get_future();
        std::thread t(&CairoDrawer::drawWay, *(drawer.get()), std::move(promise), std::move(way));
        drawing_queue->push(result.get());
        threads.emplace_back(std::move(t));
    }
    std::cout <<  "spawned"  <<std::endl;

    drawer->drawBorder();
    drawer->drawCenter();
    drawing_queue->push(true);

    drawing_queue->push(false);
    long timeSinceParsingStarted= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - parsingStarted).count();
    std::cout << "Parsing/Drawing took "<<timeSinceParsingStarted<<" milliseconds"  <<std::endl;
    delete state;

    for(int i=0; i<threads.size(); ++i){
        ( std::move( threads.at(i) )).join();
    }
    return "Finished Drawing";
}

