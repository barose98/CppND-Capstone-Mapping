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

void OSMDataParser::parseOSMXML(Cairo::RefPtr<Cairo::Context> context)
{
    std::cout << "osm data parse"  <<std::endl;
    //XML_Parser parser = XML_ParserCreate(NULL);

    std::string xml_data = "";
    do{//(parser_queue->hasMoreData()){
        xml_data+= parser_queue->pull() ;
        std::cout << ".";
    }while( !xml_data.empty() && xml_data.substr(xml_data.length()-7 , 6 )  != "</osm>");



    std::cout <<  "Drawing" <<std::endl;
    context ->set_line_width(2.0);
    context->set_source_rgba( 1.0, 0.0, 0.0, 1.0);

    context ->stroke();
}
