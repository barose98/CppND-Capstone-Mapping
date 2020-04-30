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
struct map_center_t{
    float latitude;
    float longitude;
};
struct bounding_box_t {
    float left;
    float top;
    float right;
    float bottom;
} ;

class OSMDownloader {
public:
    OSMDownloader();
    ~OSMDownloader();
    OSMDownloader(const OSMDownloader &other);
    OSMDownloader &operator=(const OSMDownloader &other);
    map_center_t getCurrentCenter() const;
    void setCurrentCenter(map_center_t currentCenter);

private:
     float map_size;
    map_center_t current_center;
};

#endif /* OSMDOWNLOADER_H_ */
