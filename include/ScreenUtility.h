/*
 * ScreenUtility.h
 *
 *  Created on: May 10, 2020
 *      Author: roseba
 */

#ifndef SRC_SCREENUTILITY_H_
#define SRC_SCREENUTILITY_H_

#include <MappingStructs.h>
#include <iostream>

class ScreenUtility {
public:
    const screen_point_t& getPressedAt() const;
    void setPressedAt(const screen_point_t &pressedAt);
    void moveOrigin(double xDelta, double yDelta);
    const screen_size_t& getAllocated() const;
    void setAllocated(const screen_size_t &allocated);
    const screen_point_t& getOrigin() const;
    void setOrigin(const screen_point_t &origin);
    bool isRecenter() const;
    void setRecenter(bool recenter = true);
    const screen_size_t& getMapPixelSize() const;
    void setMapPixelCenter(const screen_point_t mapPixelCenter);
    screen_point_t getMapPixelCenter() const;


private:
    screen_point_t pressedAt;
    screen_point_t origin;
    screen_size_t allocated;
    bool recenter = true;
    screen_size_t map_pixel_size = screen_size_t(MAP_PIXEL_SIZE,MAP_PIXEL_SIZE);
    screen_point_t map_pixel_center = screen_point_t(MAP_PIXEL_SIZE/2.0,MAP_PIXEL_SIZE/2.0);
};

#endif /* SRC_SCREENUTILITY_H_ */
