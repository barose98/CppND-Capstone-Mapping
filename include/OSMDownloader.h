/*
 * OSMDownloader.h
 *
 *  Created on: Apr 30, 2020
 *      Author: Barrett Rose
 */

#ifndef OSMDOWNLOADER_H_
#define OSMDOWNLOADER_H_
/**
This class uses libcurl to download data in XML format from the OSM mirror.
It specifies a callback to write the data as it comes in to the OSMDownloadQueue class.
*/

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
    OSMDownloader(const OSMDownloader &other);
    OSMDownloader( OSMDownloader &&other);

    OSMDownloader operator=(const OSMDownloader &other);
    OSMDownloader operator=(OSMDownloader &&other);
    ~OSMDownloader();
    /**
    This is the main function to initiate downloading with libcurl.
    It initializes the curl connection and performs the download.
    */
    std::string downloadOSMap(bounding_box_t box);
    /**
     * This is the function where libcurl options are set.
     * The callback functions are set, as well as the data structures,
     *  to which pointers are passed to the callbacks are specified.
     */
    bool initMappingCurl(CURL *&conn, const char *url);
    /**
     * This is the method libcurl uses as a callback to write data.
     * The function also pushes data to the DownloaderQueue.
     * The function name is set in the initMappingcurl function.
     */
    static int osmMapWriter(char *data,  size_t size,  size_t nmemb, std::shared_ptr<OSMDownloadQueue< std::string>> *writerData);
    static int osmHeaderWriter(char *data,  size_t size,  size_t nmemb, std::shared_ptr<OSMDownloadQueue< std::string>> *writerData);

private:
    std::shared_ptr<OSMDownloadQueue< std::string>> downloader_queue;
    std::chrono::time_point<std::chrono::system_clock> downloadStarted;
    char errorBuffer[CURL_ERROR_SIZE];
    std::string buffer;

};


#endif /* OSMDOWNLOADER_H_ */
