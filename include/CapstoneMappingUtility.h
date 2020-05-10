/*
 * ScreenLatLonUtility.h
 *
 *  Created on: May 1, 2020
 *      Author: roseba
 */

#ifndef SRC_CAPSTONEMAPPINGUTILITY_H_
#define SRC_CAPSTONEMAPPINGUTILITY_H_

#define MAP_PIXEL_SIZE 2500.0
#define MAP_LATLON_SIZE 0.025
 #define DEGREES_PER_PIXEL MAP_LATLON_SIZE / MAP_PIXEL_SIZE

#include <iostream>
#include <memory>

struct latlon_point_t{
    latlon_point_t();
    latlon_point_t(float latitude,float longitude);
    float latitude;
    float longitude;
};
struct bounding_box_t {
    bounding_box_t(latlon_point_t center, float edge);
    float left;
    float top;
    float right;
    float bottom;
} ;
struct screen_point_t{
    screen_point_t();
    screen_point_t(double x, double y);
    double X;
    double Y;
};
struct screen_size_t{
    screen_size_t();
    screen_size_t(double w,double h);
    double width;
    double height;
};
class CapstoneMappingUtility {
public:
    CapstoneMappingUtility();
};

#endif /* SRC_SCREENLATLONUTILITY_H_ */
