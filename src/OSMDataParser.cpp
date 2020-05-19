/*
 * OSMDataParser.cpp
 *
 *  Created on: May 6, 2020
 *      Author: roseba
 */

#include "OSMDataParser.h"

OSMDataParser::OSMDataParser(std::shared_ptr<CapstoneMappingQueue<std::string>> queue): parser_queue(queue)
{
    std::cout <<  "OSM Parser Constructor  " <<this<<std::endl;
}

OSMDataParser::~OSMDataParser()
{
    std::cout <<  "OSM Parser Destructor "<<this<<std::endl;
}

void OSMDataParser::parseOSMXML(std::shared_ptr<MappingCairoDrawer> drawer, std::stringstream &xml_data){
    std::cout << "osm data parse "  <<std::endl;
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
                state->drawer->drawNode(node);
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
//                                        for(int i=0;attrs[i];i+=2){
//                                            std::cout <<  attrs[i]<<"="<<attrs[i+1]  <<" ";
//                                        }
                    }

            }
        }

            };

      auto endElement = [](void *userData, const XML_Char *name){
      struct ParserStruct *state = (struct ParserStruct *) userData;
      if ( std::string(name)=="way"){
          state->drawer->drawWay(state->currentWay);
      }
      state->depth--;
    };

    ParserStruct *state = new ParserStruct();
    state->ok =1;
    state->drawer = drawer;

    XML_Parser parser = XML_ParserCreateNS(NULL, '\0');
    XML_SetUserData(parser, state);
    XML_SetElementHandler(parser, startElement, endElement);
    if(state->ok && XML_Parse(parser, xml_data.str().c_str(), xml_data.str().size(), 0) == 0) {
        int error_code = XML_GetErrorCode(parser);
        std::cerr << "ERROR PARSING"   <<std::endl;
    }

    delete state;
    XML_ParserFree(parser);
}
void OSMDataParser::receiveOSMXML(std::shared_ptr<MappingCairoDrawer> drawer)
{
    std::cout << "osm data receive "  <<std::endl;
    std::stringstream xml_data;
    do{
//        std::string chunk
        xml_data<< parser_queue->pull() ;
        if(xml_data.str().find("<downloaderError/>") != std::string::npos){
            std::cerr <<  xml_data.str()  <<std::endl;
            xml_data = std::stringstream("");
            break;
        }
    }while( !xml_data.str().empty() && xml_data.str().substr(xml_data.str().length()-7 , 6 )  != "</osm>");

    if(!xml_data.str().empty()){
        this->parseOSMXML(drawer, xml_data);
    }
    drawer->drawGrid();
    std::cout <<  "Drawing" <<std::endl;
    //Paint the background.

}


