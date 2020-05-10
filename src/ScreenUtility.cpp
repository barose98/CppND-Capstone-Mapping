/*
 * ScreenUtility.cpp
 *
 *  Created on: May 10, 2020
 *      Author: roseba
 */

#include "ScreenUtility.h"

const screen_point_t& ScreenUtility::getPressedAt() const
{
    return pressedAt;
}

void ScreenUtility::setPressedAt(const screen_point_t &pressedAt)
{
    this->pressedAt = pressedAt;
}

void ScreenUtility::moveOrigin(double xDelta, double yDelta)
{
    double translateX =  (xDelta - pressedAt.X)*-1.0;
     double translateY = (yDelta - pressedAt.Y)*-1.0;

         double edgeX =MAP_PIXEL_SIZE - allocated.width;
         double edgeY = MAP_PIXEL_SIZE - allocated.height;
         origin.X += translateX;
         origin.Y += translateY;
         if(origin.X < 0){
             origin.X=0.0;
//                recenter = true;
         }
         if(origin.Y < 0){
             origin.Y=0.0;
//                recenter = true;
         }
         if(origin.X > edgeX){
             origin.X=edgeX;
//                recenter = true;
         }
         if(origin.Y > edgeY){
             origin.Y=edgeY;
//                recenter = true;
         }


}

const screen_size_t& ScreenUtility::getAllocated() const
{
    return allocated;
}

void ScreenUtility::setAllocated(const screen_size_t &allocated)
{
    this->allocated = allocated;
}

const screen_point_t& ScreenUtility::getOrigin() const
{
    return origin;
}

void ScreenUtility::setOrigin(const screen_point_t &origin)
{
    this->origin = origin;
}

bool ScreenUtility::isRecenter() const
{
    return recenter;
}

void ScreenUtility::setRecenter(bool recenter )
{
    this->recenter = recenter;
}
