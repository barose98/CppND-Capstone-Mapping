/*
 * LatLonUtility.cpp
 *
 *  Created on: May 10, 2020
 *      Author: roseba
 */

#include "LatLonUtility.h"

latlon_point_t LatLonUtility::calculateAnyLatLonPoint(screen_point_t big_query_point) const
{
//    latlon_point_t offset_percent(float(offset.y/map_pixel_size.h), float(offset.x/map_pixel_size.w) );
//    latlon_point_t little_percent(float(released.y/allocated.h),  float(released.x/allocated.w) )  ;
//    latlon_point_t big_percent(float((offset.y + released.y) /map_pixel_size.h),  float((offset.x +released.x) /map_pixel_size.w) )  ;

//    screen_point_t diff_pixels( double(  mapPixelCenter.X - ( big_query_point.X + offset.X) ) , double( mapPixelCenter.Y - ( big_query_point.Y + offset.Y )) );
//    latlon_point_t latlon_diff( float(diff_pixels.Y * DEGREES_PER_PIXEL) , float(diff_pixels.X * -DEGREES_PER_PIXEL) );
    return latlon_point_t( (big_query_point.Y * DEGREES_PER_PIXEL)+getBigMapLatlonOrigin().latitude , (big_query_point.X * DEGREES_PER_PIXEL)+getBigMapLatlonOrigin().longitude);
    }

    float LatLonUtility::getBigMapLatlonEdge() const
    {
        return std::sqrt(MAP_LATLON_SIZE);
    }

    float LatLonUtility::getBigMapLatlonSize() const
    {
        return MAP_LATLON_SIZE;
    }

    latlon_point_t LatLonUtility::getBigMapLatlonOrigin() const
    {
        return big_map_latlon_origin;
    }

    void LatLonUtility::setBigMapLatlonOrigin(latlon_point_t bigMapLatlonOrigin)
    {
        big_map_latlon_origin = bigMapLatlonOrigin;
}

latlon_point_t LatLonUtility::getLittleMapLatlonCenter() const
{
}

void LatLonUtility::setLittleMapLatlonCenter(latlon_point_t mapLatlonCenter)
{
}
