/*
 * OSMDataParser.h
 *
 *  Created on: May 6, 2020
 *      Author: Barrett Rose
 */

#ifndef SRC_OSMDATAPARSER_H_
#define SRC_OSMDATAPARSER_H_
/**
 * This class is used by CapstoneMapping class, which spawns a
 * thread to run receiveOSMXML() function, which pulls data chunk by
 * chunk from the OSMDownloadQueue and appends it to a string,
 * which can then go to the parseOSMXML() method.
 *
 * This method starts the expat parser.
 * This function also defines lambda functions which serve as
 * callbacks that handle  the starElement and endElement events for the parser.
 *
 * After the data is parsed and the relevent data is stored in the CairoDrawer class,
 * it repeatedly calls the drawWay() of that class. It also pushes booleans
 * to the DrawlingQueue class, which notifies the DrawlingArea
 *  class that drawing is happening and it should incrementally redraw itself.
 * */

#include <CairoDrawer.h>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include <expat.h>
#include <OSMDownloadQueue.h>
#include <OSMDrawingQueue.h>
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
    OSMDataParser( std::shared_ptr<OSMDownloadQueue<std::string>> queue,  std::shared_ptr<OSMDrawingQueue<bool>> draw_queue);
    OSMDataParser(const OSMDataParser &other);
    OSMDataParser(OSMDataParser &&other);
    OSMDataParser operator=(const OSMDataParser &other);
    OSMDataParser operator=(OSMDataParser &&other);
    ~OSMDataParser();
    std::string receiveOSMXML(std::shared_ptr<CairoDrawer> drawer);
    void parseOSMXML(std::shared_ptr<CairoDrawer> drawer, std::stringstream &xml_data);
private:
    std::chrono::time_point<std::chrono::system_clock> parsingStarted;
    std::shared_ptr<OSMDownloadQueue< std::string>> parser_queue;
    std::shared_ptr<OSMDrawingQueue<bool>> drawing_queue;
    ParserStruct *state;
};

#endif /* SRC_OSMDATAPARSER_H_ */
