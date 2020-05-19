/*
 * ScreenUtility.cpp
 *
 *  Created on: May 10, 2020
 *      Author: roseba
 */

#include "ScreenUtility.h"

const screen_point_t ScreenUtility::getPressedAt() const
{
    return pressedAt;
}

void ScreenUtility::setPressedAt(const screen_point_t pressedAt)
{
    this->pressedAt = pressedAt;
}

void ScreenUtility::moveOffset(double xDelta, double yDelta)
{
    double translateX =  (xDelta - pressedAt.X)*-1.0;
     double translateY = (yDelta - pressedAt.Y)*-1.0;

         double edgeX =MAP_PIXEL_SIZE - allocated.width;
         double edgeY = MAP_PIXEL_SIZE - allocated.height;
         offset.X += translateX;
         offset.Y += translateY;
         if(offset.X < 0){
             offset.X=0.0;
//                recenter = true;
         }
         if(offset.Y < 0){
             offset.Y=0.0;
//                recenter = true;
         }
         if(offset.X > edgeX){
             offset.X=edgeX;
//                recenter = true;
         }
         if(offset.Y > edgeY){
             offset.Y=edgeY;
//                recenter = true;
         }


}

const screen_size_t ScreenUtility::getAllocated() const
{
    return allocated;
}

void ScreenUtility::setAllocated(const screen_size_t allocated)
{
    this->allocated = allocated;
}

const screen_point_t ScreenUtility::getOffset() const
{
    return offset;
}

void ScreenUtility::setOffset(const screen_point_t origin)
{
    this->offset = origin;
}

bool ScreenUtility::isRecenter() const
{
    return recenter;
}

void ScreenUtility::setRecenter(bool recenter )
{
    this->recenter = recenter;
}
const screen_size_t ScreenUtility::getBigMapPixelSize() const
{
    return screen_size_t(MAP_PIXEL_SIZE,MAP_PIXEL_SIZE);
}
screen_point_t ScreenUtility::getBigMapPixelCenter() const
{
    return screen_point_t(MAP_PIXEL_SIZE/2,MAP_PIXEL_SIZE/2);
}

screen_point_t ScreenUtility::calculateAnyScreenPoint(percentage_point_t big_query_point) const
{
    return screen_point_t(big_query_point.percentX * getBigMapPixelSize().width,
                                            big_query_point.percentY * getBigMapPixelSize().height  );
}

percentage_point_t ScreenUtility::calculateAnyScreenPercentage(screen_point_t big_query_point) const
{
        return percentage_point_t(float(big_query_point.X / getBigMapPixelSize().width),
                                                        float(big_query_point.Y / getBigMapPixelSize().height)  );
}
