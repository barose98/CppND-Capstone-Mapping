/*
 * MappingSAXHandler.cpp
 *
 *  Created on: May 4, 2020
 *      Author: roseba
 */

#include "MappingSAXHandler.h"

MappingSAXHandler::~MappingSAXHandler()
{

}

MappingSAXHandler::MappingSAXHandler()
{


}

void MappingSAXHandler::startElement(const XMLCh *name, xercesc::AttributeList &attrs)
{
    char* message =  xercesc::XMLString::transcode(name);
    std::cout << "I saw element: "<< message <<  std::endl;
    xercesc::XMLString::release(&message);
}

void MappingSAXHandler::fatalError(const xercesc::SAXParseException &exception)
{
    char* message = xercesc::XMLString::transcode(exception.getMessage());
    std::cout << "Fatal Error: " << message<< " at line: " << exception.getLineNumber()<<  std::endl;
      xercesc::XMLString::release(&message);
}
