/*
 * OSMDataParser.h
 *
 *  Created on: May 6, 2020
 *      Author: roseba
 */

#ifndef SRC_OSMDATAPARSER_H_
#define SRC_OSMDATAPARSER_H_
#include <iostream>
#include <memory>

#include <gtkmm.h>

#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/util/XMLString.hpp>

#include "MappingSAXHandler.h"

class OSMDataParser {
public:
    OSMDataParser();
    ~OSMDataParser();
    void parseOSMXML(std::string &buffer, Cairo::RefPtr<Cairo::Context> context );
};

#endif /* SRC_OSMDATAPARSER_H_ */
