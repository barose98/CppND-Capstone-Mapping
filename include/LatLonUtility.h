/*
 * LatLonUtility.h
 *
 *  Created on: May 10, 2020
 *      Author: roseba
 */

#ifndef SRC_LATLONUTILITY_H_
#define SRC_LATLONUTILITY_H_
#include <MappingStructs.h>
#include <cmath>

class LatLonUtility {
public:
    latlon_point_t calculateAnyLatLonPoint(percentage_point_t big_query_point) const;
    percentage_point_t calculateAnyLatLonPercentage(latlon_point_t big_query_point) const;
    latlon_point_t calculateBigMapLatlonOrigin() const;

    latlon_point_t getBigMapLatlonCenter() const;
    latlon_point_t getLittleMapLatlonCenter() const;
    float getBigMapLatlonSize() const;
    float getBigMapLatlonEdge() const;

    void setLittleMapLatlonCenter(latlon_point_t mapLatlonCenter);
    void setBigMapLatlonEdge(float bigMapLatlonEdge = std::sqrt(MAP_LATLON_SIZE));
    void setBigMapLatlonSize(float bigMapLatlonSize = MAP_LATLON_SIZE);
    void setBigMapLatlonCenter(latlon_point_t bigMapLatlonCenter);

private:
    latlon_point_t big_map_latlon_center;
};

#endif /* SRC_LATLONUTILITY_H_ */
