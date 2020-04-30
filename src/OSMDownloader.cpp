/*
 * OSMDownloader.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: roseba
 */

#include "OSMDownloader.h"

OSMDownloader::OSMDownloader():map_size(0.25)
{
    // TODO Auto-generated constructor stub
    std::cout <<  "OSMD Constructor "<<this  <<std::endl;
}

OSMDownloader::~OSMDownloader()
{
    // TODO Auto-generated destructor stub
    std::cout <<  "OSMD Destructor "<<this  <<std::endl;
}

map_center_t OSMDownloader::getCurrentCenter() const
{
    return current_center;
}

void OSMDownloader::setCurrentCenter(map_center_t currentCenter)
{
    std::cout <<this<<" https://overpass-api.de/api/map?bbox="<<currentCenter.longitude-.025<<","<<currentCenter.latitude-.025 <<","<<currentCenter.longitude+.025<<","<<currentCenter.latitude+.025   <<std::endl;
    current_center.latitude = currentCenter.latitude;
    current_center.longitude = currentCenter.longitude;
}

OSMDownloader::OSMDownloader(const OSMDownloader &other)
{
    std::cout <<  "OSMD copy"  <<std::endl;
}

OSMDownloader& OSMDownloader::operator =(const OSMDownloader &other)
{
    std::cout <<  "OSMD copy assignment"  <<std::endl;
}
