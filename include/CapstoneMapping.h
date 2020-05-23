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
#include <string>
#include <gtkmm.h>
#include <MappingStructs.h>
#include <OSMDownloadQueue.h>
#include "OSMDownloader.h"
#include "OSMDataParser.h"
 #include "ScreenUtility.h"
#include "LatLonUtility.h"

class CapstoneMapping {
public:
    CapstoneMapping();
    ~CapstoneMapping();

    const Cairo::RefPtr<Cairo::Surface>& getMappingSurface() const;
/**
 *     This function creates the big Cairo Surface.
    It spawns new thread objects to perform libcurl downloading,
    and another thread to do the XML parsing with expat and drawing with Cairo.
    */
    void createBigMap();
    std::shared_ptr<OSMDownloadQueue<std::string>> mapping_queue;
    std::shared_ptr< LatLonUtility> latlon_utility ;
    std::shared_ptr< ScreenUtility> screen_utility ;
    std::unique_ptr< OSMDownloader> downloader;
    std::unique_ptr<OSMDataParser> parser;
    std::shared_ptr<CairoDrawer> drawer;
    std::thread getting_thread;
    std::thread parsing_thread;

private:
    Cairo::RefPtr<Cairo::Surface> mapping_surface;

};

#endif /* SRC_CAPSTONEMAPPING_H_ */
