/*
 * OSMDownloader.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: roseba
 */

#include "OSMDownloader.h"


OSMDownloader::OSMDownloader()
{
    // TODO Auto-generated constructor stub
    std::cout <<  "OSMD Constructor "<<this  <<std::endl;
}

OSMDownloader::~OSMDownloader()
{
    // TODO Auto-generated destructor stub
    std::cout <<  "OSMD Destructor "<<this  <<std::endl;
}


OSMDownloader::OSMDownloader(const OSMDownloader &other)
{
    std::cout <<  "OSMD copy"  <<std::endl;

}

OSMDownloader& OSMDownloader::operator =(const OSMDownloader &other)
{
    std::cout <<  "OSMD copy assignment"  <<std::endl;
    return *this;
}
