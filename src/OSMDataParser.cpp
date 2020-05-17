/*
 * OSMDataParser.cpp
 *
 *  Created on: May 6, 2020
 *      Author: roseba
 */

#include "OSMDataParser.h"

OSMDataParser::OSMDataParser(std::shared_ptr<CapstoneMappingQueue<std::string>> queue): parser_queue(queue)
{
    //
    std::cout <<  "OSM Parser Constructor  " <<this<<std::endl;
}

OSMDataParser::~OSMDataParser()
{
    std::cout <<  "OSM Parser Destructor "<<this<<std::endl;
}

void OSMDataParser::parseOSMXML(Cairo::RefPtr<Cairo::Surface> &mapping_surface, std::stringstream &xml_data){
    std::cout << "osm data parse "  <<std::endl;

    auto  startElement = [](void *userData, const XML_Char *name, const XML_Char **atts)
            {
        struct ParserStruct *state = (struct ParserStruct *) userData;
        state->tags++;
        state->depth++;
        std::cout <<  name  <<std::endl;
        /* Get a clean slate for reading in character data. */
        delete state->characters.memory;
        state->characters.memory = NULL;
        state->characters.size = 0;
            };

    auto endElement = [](void *userData, const XML_Char *name){
      struct ParserStruct *state = (struct ParserStruct *) userData;
      state->depth--;
    };
    ParserStruct *state = new ParserStruct();
    state->ok =1;
    XML_Parser parser = XML_ParserCreateNS(NULL, '\0');
    XML_SetUserData(parser, state);
    XML_SetElementHandler(parser, startElement, endElement);
    if(state->ok && XML_Parse(parser, xml_data.str().c_str(), xml_data.str().size(), 0) == 0) {
        int error_code = XML_GetErrorCode(parser);
        std::cerr << "ERROR PARSING"   <<std::endl;
    }

    delete state->characters.memory;
    delete state;
    XML_ParserFree(parser);
}
void OSMDataParser::receiveOSMXML(Cairo::RefPtr<Cairo::Surface> mapping_surface)
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

    if(!xml_data.str().empty())
        parseOSMXML(mapping_surface, xml_data);
    std::cout <<  "Drawing" <<std::endl;
    //Paint the background.

    int pixel_width = 5000;
    int pixel_height = 5000;
    int i;
    int grid_incr = pixel_width/3;
    Cairo::RefPtr<Cairo::Context> context = Cairo::Context::create(mapping_surface);
    context->set_source_rgba( 0.0, 0.0, 0.0, 0.1);
    context->paint();
    //Draw some horizontal lines.
    context->set_source_rgba( 0.0, 1.0, 0.0, 1.0);
    for(i=0;i<pixel_width;i+=grid_incr)
      {
        context->move_to( 0.0, double(i));
        context->line_to( pixel_width, double(i));
        context->stroke();
      }
    //Draw some vertical lines.
    for(i=0;i<pixel_height;i+= grid_incr)
      {
        context->move_to( double(i), 0.0);
        context->line_to(  double(i), pixel_height);
        context->stroke();
      }
    //Outside box.
    context->set_line_width( 16.0);
    context->set_source_rgba( 1.0, 0.0, 1.0, 1.0);
    context->rectangle( 0.0, 0.0, pixel_width, pixel_height);

    context ->stroke();
}
