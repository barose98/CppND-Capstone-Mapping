/*
 * CapstoneMapping.h
 *
 *  Created on: Apr 27, 2020
 *      Author: roseba
 */

#ifndef SRC_CAPSTONEMAPPING_H_
#define SRC_CAPSTONEMAPPING_H_

#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <gtkmm.h>
#include <MappingStructs.h>
#include "MappingCairoDrawer.h"
#include "OSMDownloader.h"
#include "OSMDataParser.h"
 #include "CapstoneMappingQueue.h"
#include "ScreenUtility.h"
#include "LatLonUtility.h"

class CapstoneMapping {
public:
    CapstoneMapping();
    ~CapstoneMapping();

    const Cairo::RefPtr<Cairo::Surface>& getMappingSurface() const;
    void createBigMap();
    void setInitialBigMapLatlonCenter(latlon_point_t bigMapLatlonCenter);
    std::shared_ptr<CapstoneMappingQueue<std::string>> mapping_queue;
    std::shared_ptr< LatLonUtility> latlon_utility ;
    std::shared_ptr< ScreenUtility> screen_utility ;
    std::unique_ptr< OSMDownloader> downloader;
    std::unique_ptr<OSMDataParser> parser;
    std::shared_ptr<MappingCairoDrawer> drawer;
    std::thread getting_thread;
    std::thread parsing_thread;

private:
    Cairo::RefPtr<Cairo::Surface> mapping_surface;

};

#endif /* SRC_CAPSTONEMAPPING_H_ */
