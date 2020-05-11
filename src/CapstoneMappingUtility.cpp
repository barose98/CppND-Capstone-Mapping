/*
 * ScreenLatLonUtility.cpp
 *
 *  Created on: May 1, 2020
 *      Author: roseba
 */
#include <MappingStructs.h>

latlon_point_t::latlon_point_t():latitude(0.0),longitude(0.0)
{
}

latlon_point_t::latlon_point_t(float lat, float lon):latitude(lat),longitude(lon)
{
}

screen_size_t::screen_size_t():width(MAP_PIXEL_SIZE),height(MAP_PIXEL_SIZE)
{
}

screen_size_t::screen_size_t(double w, double h):width(w),height(h)
{
}

screen_point_t::screen_point_t():X(0.0),Y(0.0)
{
}

screen_point_t::screen_point_t(double x, double y):X(x),Y(y)
{
}

bounding_box_t::bounding_box_t(latlon_point_t center,float edge)
{
    left = center.longitude-edge/2.0;
        top= center.latitude+edge/2.0;
        right= center.longitude+edge/2.0;
        bottom= center.latitude-edge/2.0;
}
