/*
 * OSMDataParser.h
 *
 *  Created on: May 6, 2020
 *      Author: roseba
 */

#ifndef SRC_OSMDATAPARSER_H_
#define SRC_OSMDATAPARSER_H_
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include <expat.h>
#include <memory>
#include "CapstoneMappingQueue.h"
#include "MappingStructs.h"
#include "MappingCairoDrawer.h"

struct ParserStruct {
  int ok;
  std::string node_name = "";
  size_t depth;
  WayStruct currentWay;
  std::shared_ptr<MappingCairoDrawer> drawer;
};

class OSMDataParser {
public:
    OSMDataParser( std::shared_ptr<CapstoneMappingQueue<std::string>> queue);
    ~OSMDataParser();
    void receiveOSMXML(std::shared_ptr<MappingCairoDrawer> drawer);
    void parseOSMXML(std::shared_ptr<MappingCairoDrawer> drawer, std::stringstream &xml_data);
private:
    std::shared_ptr<CapstoneMappingQueue< std::string>> parser_queue;
    ParserStruct *state;
};

#endif /* SRC_OSMDATAPARSER_H_ */
