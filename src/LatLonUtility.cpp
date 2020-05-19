/*
 * LatLonUtility.cpp
 *
 *  Created on: May 10, 2020
 *      Author: roseba
 */

#include "LatLonUtility.h"

latlon_point_t LatLonUtility::calculateAnyLatLonPoint(percentage_point_t big_query_point) const
{

    return latlon_point_t( (big_query_point.percentY * getBigMapLatlonEdge())+calculateBigMapLatlonOrigin().latitude ,
                                            (big_query_point.percentX * getBigMapLatlonEdge())+calculateBigMapLatlonOrigin().longitude);
    }

    float LatLonUtility::getBigMapLatlonEdge() const
    {
        return std::sqrt(MAP_LATLON_SIZE);
    }

    float LatLonUtility::getBigMapLatlonSize() const
    {
        return MAP_LATLON_SIZE;
    }

    latlon_point_t LatLonUtility::calculateBigMapLatlonOrigin() const
    {
        return latlon_point_t(big_map_latlon_center.latitude + getBigMapLatlonEdge()/2 ,
                                                big_map_latlon_center.longitude - getBigMapLatlonEdge()/2);
    }

    percentage_point_t LatLonUtility::calculateAnyLatLonPercentage(latlon_point_t big_query_point) const
{
    latlon_point_t  diff(double(std::abs( calculateBigMapLatlonOrigin().latitude) - std::abs( big_query_point.latitude )),
                                    double( std::abs(calculateBigMapLatlonOrigin().longitude ) - std::abs(big_query_point.longitude) ));
    return percentage_point_t(diff.longitude / getBigMapLatlonEdge(), diff.latitude / getBigMapLatlonEdge());

}

    void LatLonUtility::setBigMapLatlonCenter(latlon_point_t bigMapLatlonOrigin)
    {
        big_map_latlon_center = bigMapLatlonOrigin;
}

latlon_point_t LatLonUtility::getLittleMapLatlonCenter() const
{
}

void LatLonUtility::setLittleMapLatlonCenter(latlon_point_t mapLatlonCenter)
{
}
