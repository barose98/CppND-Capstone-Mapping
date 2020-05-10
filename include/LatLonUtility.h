/*
 * LatLonUtility.h
 *
 *  Created on: May 10, 2020
 *      Author: roseba
 */

#ifndef SRC_LATLONUTILITY_H_
#define SRC_LATLONUTILITY_H_
#include <cmath>
#include "CapstoneMappingUtility.h"

class LatLonUtility {
public:
    latlon_point_t calculateAnyLatLonPoint(screen_point_t point, screen_point_t offset) const;
    float getMapLatlonSize() const;
    float getMapLatlonEdge() const;
    latlon_point_t getMapLatlonCenter() const;
    void setMapLatlonCenter(latlon_point_t mapLatlonCenter);
private:
    float map_latlon_size = MAP_LATLON_SIZE;
    float map_latlon_edge = std::sqrt(MAP_LATLON_SIZE);
    latlon_point_t map_latlon_center;
};

#endif /* SRC_LATLONUTILITY_H_ */
