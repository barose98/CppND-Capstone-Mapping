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

    OSMDownloader(std::shared_ptr<CapstoneMappingQueue<std::string>> queue);
    ~OSMDownloader();

    std::string downloadOSMap(bounding_box_t box);
    bool init_mapping_curl(CURL *&conn, const char *url);

    static int osm_map_writer(char *data,  size_t size,  size_t nmemb, std::shared_ptr<CapstoneMappingQueue< std::string>> *writerData);

private:
    std::shared_ptr<CapstoneMappingQueue< std::string>> downloader_queue;
    char errorBuffer[CURL_ERROR_SIZE];
    std::string buffer;

};


#endif /* OSMDOWNLOADER_H_ */
