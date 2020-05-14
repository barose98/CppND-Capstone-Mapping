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

void OSMDataParser::parseOSMXML(Cairo::RefPtr<Cairo::Surface> mapping_surface)
{
    std::cout << "osm data parse"  <<std::endl;
    std::string xml_data = "";
    do{//(parser_queue->hasMoreData()){
        xml_data+= parser_queue->pull() ;
        std::cout << ".";
    }while( !xml_data.empty() && xml_data.substr(xml_data.length()-7 , 6 )  != "</osm>");



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
