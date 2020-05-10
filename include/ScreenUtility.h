/*
 * ScreenUtility.h
 *
 *  Created on: May 10, 2020
 *      Author: roseba
 */

#ifndef SRC_SCREENUTILITY_H_
#define SRC_SCREENUTILITY_H_

#include <iostream>
#include "CapstoneMappingUtility.h"

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

private:
    screen_point_t pressedAt;
    screen_point_t origin;
    screen_size_t allocated;
    bool recenter = true;
};

#endif /* SRC_SCREENUTILITY_H_ */
