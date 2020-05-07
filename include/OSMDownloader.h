/*
 * OSMDownloader.h
 *
 *  Created on: Apr 30, 2020
 *      Author: roseba
 */

#ifndef OSMDOWNLOADER_H_
#define OSMDOWNLOADER_H_

 #define OSM_URL "https://overpass-api.de/api/map?bbox="

#include <iostream>
#include <sstream>
#include <curl/curl.h>

#include "CapstoneMappingUtility.h"

class OSMDownloader {
public:
    OSMDownloader();
    ~OSMDownloader();
    OSMDownloader(const OSMDownloader &other);
    OSMDownloader &operator=(const OSMDownloader &other);

    std::string downloadOSMap(bounding_box_t box);
    bool init_mapping_curl(CURL *&conn, const char *url);

    static int osm_map_writer(char *data,  size_t size,  size_t nmemb,  std::string *writerData){
        if(writerData == NULL)
          return 0;
        writerData->append(data, size*nmemb);
        std::cout <<  data;
        return size * nmemb;
    }


    char errorBuffer[CURL_ERROR_SIZE];
    std::string buffer;

};

#endif /* OSMDOWNLOADER_H_ */
