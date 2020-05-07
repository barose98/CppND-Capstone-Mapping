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
    double x;
    double y;
};
struct screen_size_t{
    screen_size_t();
    screen_size_t(double w,double h);
    double w;
    double h;
};
class CapstoneMappingUtility {
public:
    CapstoneMappingUtility();
    latlon_point_t calculateAnyLatLonPoint(screen_point_t point, screen_size_t allocated, screen_point_t offset) const;
    float getMapLatlonSize() const;
    screen_point_t getMapPixelCenter() const;
    const screen_size_t& getMapPixelSize() const;
    float getMapLatlonEdge() const;
    latlon_point_t getMapLatlonCenter() const;
    void setMapLatlonCenter(latlon_point_t mapLatlonCenter);
    void setMapPixelCenter(const screen_point_t mapPixelCenter);

private:
   screen_size_t map_pixel_size;
   screen_point_t map_pixel_center = screen_point_t(MAP_PIXEL_SIZE/2.0,MAP_PIXEL_SIZE/2.0);;
    float map_latlon_size;
    float map_latlon_edge;
    latlon_point_t map_latlon_center;

};

#endif /* SRC_SCREENLATLONUTILITY_H_ */
