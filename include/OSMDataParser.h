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
#include <gtkmm.h>

#include <expat.h>
#include "CapstoneMappingQueue.h"
#include "MappingStructs.h"
#include "ScreenUtility.h"
#include "LatLonUtility.h"

struct NodeStruct{
    std::string id;
    latlon_point_t point;
};
struct ParserStruct {
  int ok;
  std::string node_name;
  size_t depth;
  Cairo::RefPtr<Cairo::Surface> mapping_surface;
  std::vector<NodeStruct> nodes;
  std::shared_ptr< LatLonUtility> latlon_utility ;
  std::shared_ptr< ScreenUtility> screen_utility ;
};
class OSMDataParser {
public:
    OSMDataParser(std::shared_ptr< LatLonUtility> latlon_utility, std::shared_ptr<ScreenUtility> screen_utility, std::shared_ptr<CapstoneMappingQueue<std::string>> queue);
    ~OSMDataParser();
    void receiveOSMXML(Cairo::RefPtr<Cairo::Surface> mapping_surface);
    void parseOSMXML(Cairo::RefPtr<Cairo::Surface> &mapping_surface, std::stringstream &xml_data);
private:
    std::shared_ptr<CapstoneMappingQueue< std::string>> parser_queue;
    std::shared_ptr< LatLonUtility> latlon_utility ;
    std::shared_ptr< ScreenUtility> screen_utility ;
};

#endif /* SRC_OSMDATAPARSER_H_ */
