/*
 * OSMDataParser.h
 *
 *  Created on: May 6, 2020
 *      Author: Barrett Rose
 */

#ifndef SRC_OSMDATAPARSER_H_
#define SRC_OSMDATAPARSER_H_
#include <CairoDrawer.h>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include <expat.h>
#include <OSMDownloadQueue.h>
#include <memory>
#include "MappingStructs.h"

struct ParserStruct {
  int ok;
  std::string node_name = "";
  size_t depth;
  WayStruct currentWay;
  std::shared_ptr<CairoDrawer> drawer;
};

class OSMDataParser {
public:
    OSMDataParser( std::shared_ptr<OSMDownloadQueue<std::string>> queue);
    ~OSMDataParser();
    void receiveOSMXML(std::shared_ptr<CairoDrawer> drawer);
    void parseOSMXML(std::shared_ptr<CairoDrawer> drawer, std::stringstream &xml_data);
private:
    std::shared_ptr<OSMDownloadQueue< std::string>> parser_queue;
    ParserStruct *state;
};

#endif /* SRC_OSMDATAPARSER_H_ */
