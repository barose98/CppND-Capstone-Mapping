/*
 * ScreenLatLonUtility.cpp
 *
 *  Created on: May 1, 2020
 *      Author: roseba
 */
#include <CapstoneMappingUtility.h>
#include <cmath>

CapstoneMappingUtility::CapstoneMappingUtility()//:map_pixel_size(pixelSize),map_latlon_size(latlonSize)
{

    map_pixel_size = screen_size_t(MAP_PIXEL_SIZE,MAP_PIXEL_SIZE);
    map_latlon_size = MAP_LATLON_SIZE;
    map_latlon_edge = std::sqrt(MAP_LATLON_SIZE);
    std::cout << "SLLU Constructor edge"<<map_latlon_edge   <<std::endl;
}

float CapstoneMappingUtility::getMapLatlonSize() const
{
    return map_latlon_size;
}

screen_point_t CapstoneMappingUtility::getMapPixelCenter() const
{
    return map_pixel_center;
}

const screen_size_t& CapstoneMappingUtility::getMapPixelSize() const
{
    return map_pixel_size;
}

float CapstoneMappingUtility::getMapLatlonEdge() const
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

bounding_box_t::bounding_box_t(latlon_point_t center,float edge)
{
    left = center.longitude-edge/2.0;
        top= center.latitude+edge/2.0;
        right= center.longitude+edge/2.0;
        bottom= center.latitude-edge/2.0;
}

latlon_point_t CapstoneMappingUtility::getMapLatlonCenter() const
{
    return map_latlon_center;
}

void CapstoneMappingUtility::setMapLatlonCenter(latlon_point_t mapLatlonCenter)
{
    map_latlon_center = mapLatlonCenter;
}

latlon_point_t CapstoneMappingUtility::calculateAnyLatLonPoint(screen_point_t released, screen_size_t allocated,  screen_point_t offset) const
{
//    latlon_point_t offset_percent(float(offset.y/map_pixel_size.h), float(offset.x/map_pixel_size.w) );
//    latlon_point_t little_percent(float(released.y/allocated.h),  float(released.x/allocated.w) )  ;
//    latlon_point_t big_percent(float((offset.y + released.y) /map_pixel_size.h),  float((offset.x +released.x) /map_pixel_size.w) )  ;

    screen_point_t diff_pixels( double(  getMapPixelCenter().x - ( released.x + offset.x) ) , double( getMapPixelCenter().y - ( released.y + offset.y )) );
    latlon_point_t latlon_diff( float(diff_pixels.y * DEGREES_PER_PIXEL) , float(diff_pixels.x * -DEGREES_PER_PIXEL) );
    return latlon_point_t(getMapLatlonCenter().latitude + latlon_diff.latitude , getMapLatlonCenter().longitude + latlon_diff.longitude);
}
void CapstoneMappingUtility::setMapPixelCenter(const screen_point_t mapPixelCenter)
{
    map_pixel_center = mapPixelCenter;
}
