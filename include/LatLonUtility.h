/*
 * LatLonUtility.h
 *
 *  Created on: May 10, 2020
 *      Author: Barrett Rose
 */

#ifndef SRC_LATLONUTILITY_H_
#define SRC_LATLONUTILITY_H_
#include <MappingStructs.h>
#include <cmath>
/**
This class has methods used by several classes to figure out things
about what the map is looking at it the terms of real world coordinates.
*/

class LatLonUtility {
public:
    latlon_point_t calculateAnyLatLonPoint(percentage_point_t big_query_point) const;
    percentage_point_t calculateAnyLatLonPercentage(latlon_point_t big_query_point) const;
    latlon_point_t calculateBigMapLatlonOrigin() const;

    latlon_point_t getBigMapLatlonCenter() const;
    float getBigMapLatlonSize() const;
    float getBigMapLatlonEdge() const;

    void setBigMapLatlonEdge(float bigMapLatlonEdge = std::sqrt(MAP_LATLON_SIZE));
    void setBigMapLatlonSize(float bigMapLatlonSize = MAP_LATLON_SIZE);
    void setBigMapLatlonCenter(latlon_point_t bigMapLatlonCenter);

private:
    latlon_point_t big_map_latlon_center;
};

#endif /* SRC_LATLONUTILITY_H_ */
