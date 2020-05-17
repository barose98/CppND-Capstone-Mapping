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
#include <memory>
#include <gtkmm.h>

#include <expat.h>
#include "CapstoneMappingQueue.h"
struct MemoryStruct {
  char *memory;
  size_t size;
};

struct ParserStruct {
  int ok;
  size_t tags;
  size_t depth;
  struct MemoryStruct characters;
};
class OSMDataParser {
public:
    OSMDataParser(std::shared_ptr<CapstoneMappingQueue<std::string>> queue);
    ~OSMDataParser();
    void receiveOSMXML(Cairo::RefPtr<Cairo::Surface> mapping_surface);
    void parseOSMXML(Cairo::RefPtr<Cairo::Surface> &mapping_surface, std::stringstream &xml_data);
private:
    std::shared_ptr<CapstoneMappingQueue< std::string>> parser_queue;
};

#endif /* SRC_OSMDATAPARSER_H_ */
