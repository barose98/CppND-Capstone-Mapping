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
#include "OSMDownloader.h"
 #include "CapstoneMappingQueue.h"
#include "CapstoneMappingUtility.h"
#include "ScreenUtility.h"
#include "LatLonUtility.h"

class CapstoneMapping {
public:
    CapstoneMapping();
    ~CapstoneMapping();
//    CapstoneMapping(const CapstoneMapping& other);
//    CapstoneMapping &operator=(const CapstoneMapping& other);

    const Cairo::RefPtr<Cairo::Surface>& getMappingSurface() const;
    void createBigMap();

    std::shared_ptr<CapstoneMappingQueue<std::string>> mapping_queue;
    std::unique_ptr< LatLonUtility> latlon_utility ;
    std::unique_ptr< ScreenUtility> screen_utility ;
    std::unique_ptr< OSMDownloader> downloader;

private:
    std::thread getting_thread;
    Cairo::RefPtr<Cairo::Surface> mapping_surface;


};

#endif /* SRC_CAPSTONEMAPPING_H_ */
