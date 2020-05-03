/*
 * OSMDownloader.h
 *
 *  Created on: Apr 30, 2020
 *      Author: roseba
 */

#ifndef OSMDOWNLOADER_H_
#define OSMDOWNLOADER_H_

#include <iostream>
#include <curl/curl.h>

#include "ScreenLatLonUtility.h"

class OSMDownloader {
public:
    OSMDownloader();
    ~OSMDownloader();
    OSMDownloader(const OSMDownloader &other);
    OSMDownloader &operator=(const OSMDownloader &other);

};

#endif /* OSMDOWNLOADER_H_ */
