/*
 * OSMDownloader.h
 *
 *  Created on: Apr 30, 2020
 *      Author: roseba
 */

#ifndef OSMDOWNLOADER_H_
#define OSMDOWNLOADER_H_

 #define OSM_URL "https://overpass-api.de/api/map?bbox="

#include <memory>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <curl/curl.h>

#include <MappingStructs.h>
#include "CapstoneMappingQueue.h"

class OSMDownloader {
public:
    std::shared_ptr<CapstoneMappingQueue< std::string>> mapping_queue;

    OSMDownloader();
    ~OSMDownloader();
    OSMDownloader(const OSMDownloader &other);
    OSMDownloader &operator=(const OSMDownloader &other);

    std::string downloadOSMap(bounding_box_t box);
    bool init_mapping_curl(CURL *&conn, const char *url);

    static int osm_map_writer(char *data,  size_t size,  size_t nmemb, void* writerData);

    char errorBuffer[CURL_ERROR_SIZE];
    std::string buffer;

};


#endif /* OSMDOWNLOADER_H_ */
