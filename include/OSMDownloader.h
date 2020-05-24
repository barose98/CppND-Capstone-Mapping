/*
 * OSMDownloader.h
 *
 *  Created on: Apr 30, 2020
 *      Author: Barrett Rose
 */

#ifndef OSMDOWNLOADER_H_
#define OSMDOWNLOADER_H_

 #define OSM_URL "https://overpass-api.de/api/interpreter"

#include <memory>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <curl/curl.h>

#include <MappingStructs.h>
#include <OSMDownloadQueue.h>

class OSMDownloader {
public:

    OSMDownloader(std::shared_ptr<OSMDownloadQueue<std::string>> queue);
    ~OSMDownloader();

    std::string downloadOSMap(bounding_box_t box);
    bool initMappingCurl(CURL *&conn, const char *url);

    static int osmMapWriter(char *data,  size_t size,  size_t nmemb, std::shared_ptr<OSMDownloadQueue< std::string>> *writerData);
    static int osmHeaderWriter(char *data,  size_t size,  size_t nmemb, std::shared_ptr<OSMDownloadQueue< std::string>> *writerData);

private:
    std::shared_ptr<OSMDownloadQueue< std::string>> downloader_queue;
    std::chrono::time_point<std::chrono::system_clock> downloadStarted;
    char errorBuffer[CURL_ERROR_SIZE];
    std::string buffer;

};


#endif /* OSMDOWNLOADER_H_ */
