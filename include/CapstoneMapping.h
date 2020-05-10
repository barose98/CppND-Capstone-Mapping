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
#include <future>
#include <gtkmm.h>
#include "OSMDownloader.h"
 #include "CapstoneMappingQueue.h"
#include "CapstoneMappingUtility.h"

class CapstoneMapping {
public:
    CapstoneMapping();
    ~CapstoneMapping();
//    CapstoneMapping(const CapstoneMapping& other);
//    CapstoneMapping &operator=(const CapstoneMapping& other);

    const Cairo::RefPtr<Cairo::Surface>& getMappingSurface() const;
    void createBigMap();

    std::shared_ptr<CapstoneMappingQueue<char*>> mapping_queue;
    std::unique_ptr< CapstoneMappingUtility> latlon_utility ;
    std::unique_ptr< OSMDownloader> downloader;

private:
    std::thread getting_thread;
    Cairo::RefPtr<Cairo::Surface> mapping_surface;


};

#endif /* SRC_CAPSTONEMAPPING_H_ */
