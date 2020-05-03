/*
 * ScreenLatLonUtility.cpp
 *
 *  Created on: May 1, 2020
 *      Author: roseba
 */
#include <cmath>
#include "ScreenLatLonUtility.h"

ScreenLatLonUtility::ScreenLatLonUtility()//:map_pixel_size(pixelSize),map_latlon_size(latlonSize)
{
    std::cout << "SLLU Constructor"   <<std::endl;
    map_pixel_size = screen_size_t(MAP_PIXEL_SIZE,MAP_PIXEL_SIZE);
    map_latlon_size = MAP_LATLON_SIZE;
    map_latlon_edge = std::sqrt(MAP_LATLON_SIZE);
}

float ScreenLatLonUtility::getMapLatlonSize() const
{
    return map_latlon_size;
}

screen_point_t ScreenLatLonUtility::getMapPixelCenter() const
{
    return screen_point_t(MAP_PIXEL_SIZE/2.0,MAP_PIXEL_SIZE/2.0);
}

const screen_size_t& ScreenLatLonUtility::getMapPixelSize() const
{
    return map_pixel_size;
}

float ScreenLatLonUtility::getMapLatlonEdge() const
{
    return map_latlon_edge;
}

latlon_point_t::latlon_point_t():latitude(0.0),longitude(0.0)
{
}

latlon_point_t::latlon_point_t(float lat, float lon):latitude(lat),longitude(lon)
{
}

screen_size_t::screen_size_t():w(MAP_PIXEL_SIZE),h(MAP_PIXEL_SIZE)
{
}

screen_size_t::screen_size_t(double w, double h):w(w),h(h)
{
}

screen_point_t::screen_point_t():x(0.0),y(0.0)
{
}

screen_point_t::screen_point_t(double x, double y):x(x),y(y)
{
}
