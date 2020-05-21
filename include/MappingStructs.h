/*
 * ScreenLatLonUtility.h
 *
 *  Created on: May 1, 2020
 *      Author: roseba
 */

#ifndef SRC_CAPSTONEMAPPINGUTILITY_H_
#define SRC_CAPSTONEMAPPINGUTILITY_H_

#include <memory>
#include <vector>

#define MAP_PIXEL_SIZE 5000.0
#define MAP_LATLON_SIZE 0.0025
// #define DEGREES_PER_PIXEL MAP_LATLON_SIZE / MAP_PIXEL_SIZE
//#define PIXELS_PER_DEGREE MAP_PIXEL_SIZE / MAP_LATLON_SIZE


struct percentage_point_t{
    percentage_point_t();
    percentage_point_t(float X, float Y);
    float percentX;
    float percentY;
};
struct latlon_point_t{
    latlon_point_t();
    latlon_point_t(float latitude,float longitude);
    float latitude;
    float longitude;
};
struct bounding_box_t {
    bounding_box_t(latlon_point_t origin, float edge);
    float west;
    float north;
    float east;
    float south;
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

struct NodeStruct{
    std::string id;
    latlon_point_t point;
};
struct WayStruct{
    std::string id;
    std::string waterway;
    bool isWater;
    std::string highway;
    bool isBuilding;
    std::string name;
    std::vector<std::string> nds;
};
#endif /* SRC_SCREENLATLONUTILITY_H_ */
