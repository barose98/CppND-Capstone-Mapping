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
#include "CapstoneMappingQueue.h"

class OSMDataParser {
public:
    OSMDataParser(std::shared_ptr<CapstoneMappingQueue<std::string>> queue);
    ~OSMDataParser();
    void parseOSMXML(Cairo::RefPtr<Cairo::Context> context );
private:
    std::shared_ptr<CapstoneMappingQueue< std::string>> parser_queue;
};

#endif /* SRC_OSMDATAPARSER_H_ */
