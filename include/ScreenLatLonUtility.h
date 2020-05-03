/*
 * ScreenLatLonUtility.h
 *
 *  Created on: May 1, 2020
 *      Author: roseba
 */

#ifndef SRC_SCREENLATLONUTILITY_H_
#define SRC_SCREENLATLONUTILITY_H_

#define MAP_PIXEL_SIZE 2500.0
#define MAP_LATLON_SIZE 0.25

#include <iostream>
#include <memory>

struct latlon_point_t{
    latlon_point_t();
    latlon_point_t(float latitude,float longitude);
    float latitude;
    float longitude;
};
struct bounding_box_t {
    float left;
    float top;
    float right;
    float bottom;
} ;
struct screen_point_t{
    screen_point_t();
    screen_point_t(double x, double y);
    double x;
    double y;
};
struct screen_size_t{
    screen_size_t();
    screen_size_t(double w,double h);
    double w;
    double h;
};
class ScreenLatLonUtility {
public:
    ScreenLatLonUtility();
    latlon_point_t calculateAnyLatLonPoint(screen_point_t point) const;
    float getMapLatlonSize() const;
    screen_point_t getMapPixelCenter() const;
    const screen_size_t& getMapPixelSize() const;
    float getMapLatlonEdge() const;
private:
   screen_size_t map_pixel_size;
   screen_point_t map_pixel_center;
    float map_latlon_size;
    float map_latlon_edge;
    latlon_point_t map_latlon_center;

};

#endif /* SRC_SCREENLATLONUTILITY_H_ */
