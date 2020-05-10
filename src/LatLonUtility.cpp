/*
 * LatLonUtility.cpp
 *
 *  Created on: May 10, 2020
 *      Author: roseba
 */

#include "LatLonUtility.h"

float LatLonUtility::getMapLatlonSize() const
{
    return map_latlon_size;
}


float LatLonUtility::getMapLatlonEdge() const
{
    return map_latlon_edge;
}

latlon_point_t LatLonUtility::getMapLatlonCenter() const
{
    return map_latlon_center;
}

void LatLonUtility::setMapLatlonCenter(latlon_point_t mapLatlonCenter)
{
    map_latlon_center = mapLatlonCenter;
}

latlon_point_t LatLonUtility::calculateAnyLatLonPoint(screen_point_t released,  screen_point_t offset) const
{
//    latlon_point_t offset_percent(float(offset.y/map_pixel_size.h), float(offset.x/map_pixel_size.w) );
//    latlon_point_t little_percent(float(released.y/allocated.h),  float(released.x/allocated.w) )  ;
//    latlon_point_t big_percent(float((offset.y + released.y) /map_pixel_size.h),  float((offset.x +released.x) /map_pixel_size.w) )  ;

    screen_point_t diff_pixels( double(  getMapPixelCenter().X - ( released.X + offset.X) ) , double( getMapPixelCenter().Y - ( released.Y + offset.Y )) );
    latlon_point_t latlon_diff( float(diff_pixels.Y * DEGREES_PER_PIXEL) , float(diff_pixels.X * -DEGREES_PER_PIXEL) );
    return latlon_point_t(getMapLatlonCenter().latitude + latlon_diff.latitude , getMapLatlonCenter().longitude + latlon_diff.longitude);
}

