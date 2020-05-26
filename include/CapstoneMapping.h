/*
 * CapstoneMapping.h
 *
 *  Created on: Apr 27, 2020
 *      Author: Barrett Rose
 */
/**
 * The CapstoneMapping class is used by the main class to do work.
The createBigMap method spawns new thread to initiate downloading
from the Open Street Maps mirror as well as the OSM expat XML parser.

This class also holds smart pointers, mostly shared pointers,
to the other workers and Utility classes.
*/
#ifndef SRC_CAPSTONEMAPPING_H_
#define SRC_CAPSTONEMAPPING_H_

#include <CairoDrawer.h>
#include <iostream>
#include <memory>
#include <thread>
#include <future>
#include <string>
#include <chrono>
#include <gtkmm.h>
#include <MappingStructs.h>
#include <OSMDownloadQueue.h>
#include <OSMDrawingQueue.h>
#include "OSMDownloader.h"
#include "OSMDataParser.h"
 #include "ScreenUtility.h"
#include "LatLonUtility.h"

class CapstoneMapping {
public:
    CapstoneMapping(std::shared_ptr<OSMDownloadQueue<std::string>> queue, std::shared_ptr<OSMDrawingQueue<bool>> drawqueue);
    ~CapstoneMapping();

    const Cairo::RefPtr<Cairo::Surface>& getMappingSurface() const;
/**
 *     This function creates the big Cairo Surface.
    It spawns new thread objects to perform libcurl downloading,
    and another thread to do the XML parsing with expat and drawing with Cairo.
    */
    void createBigMap();
    std::shared_ptr< LatLonUtility> latlon_utility ;
    std::shared_ptr< ScreenUtility> screen_utility ;
private:
    std::shared_ptr<OSMDownloadQueue<std::string>> downloading_queue;
    std::shared_ptr<OSMDrawingQueue<bool>> drawing_queue;

    std::unique_ptr< OSMDownloader> downloader;
    std::unique_ptr<OSMDataParser> parser;
    std::shared_ptr<CairoDrawer> drawer;
    std::future<std::string> getting_future;
    std::future<std::string> parsing_future;

    Cairo::RefPtr<Cairo::Surface> mapping_surface;

};

#endif /* SRC_CAPSTONEMAPPING_H_ */
