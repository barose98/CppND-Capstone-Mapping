/*
 * OSMDataParser.cpp
 *
 *  Created on: May 6, 2020
 *      Author: roseba
 */

#include "OSMDataParser.h"

OSMDataParser::OSMDataParser()
{
    // TODO Auto-generated constructor stub

}

OSMDataParser::~OSMDataParser()
{
    // TODO Auto-generated destructor stub
}

void OSMDataParser::parseOSMXML(std::string &buffer, Cairo::RefPtr<Cairo::Context> context)
{

    std::cout << "osm data parse"  <<std::endl;
    xercesc::SAXParser* parser = new xercesc::SAXParser();
//    xercesc::MemBufInputSource source = new  xercesc::MemBufInputSource()
    try {
        xercesc::XMLPlatformUtils::Initialize();
    }
    catch (const  xercesc::XMLException& exception) {
        char* message =  xercesc::XMLString::transcode(exception.getMessage());
        std::cerr <<  message  <<std::endl;


    }
    MappingSAXHandler *mapping_handler = new MappingSAXHandler();
    xercesc::ErrorHandler *mapping_error_handler = ( xercesc::ErrorHandler*)mapping_handler;
    parser->setDocumentHandler(mapping_handler);
    parser->setErrorHandler(mapping_error_handler);

/*    try{
        parser->parse(src);
    }
    catch (const  xercesc::XMLException& toCatch) {
         char* message =  xercesc::XMLString::transcode(toCatch.getMessage());
         std::cerr << message   <<std::endl;
         xercesc::XMLString::release(&message);

     }
     catch (const  xercesc::SAXParseException& toCatch) {
         char* message =  xercesc::XMLString::transcode(toCatch.getMessage());
         std::cerr <<  message  <<std::endl;
         xercesc::XMLString::release(&message);

     }
     catch (...) {
         std::cerr << "Unexpected Exception \n" ;

     }*/
    delete parser;
    delete mapping_handler;
    context ->set_line_width(2.0);
    context->set_source_rgba( 1.0, 0.0, 0.0, 1.0);
//    context ->arc(this->latlon_utility->getMapPixelCenter().x,this->latlon_utility->getMapPixelCenter().y,25.0,0.0,6.28);
    context ->stroke();
}
