/*
 * ScreenUtility.h
 *
 *  Created on: May 10, 2020
 *      Author: Barrett Rose
 */
/**

This class has some private variables and public methods to help
the main GTK application to keep track of the offset, which specifies
where the Cairo Drawling area's source is compared to the big map In the "background".

The "Calculate-" methods also allow for figuring screen points from a percentage and vice versa.
*/

#ifndef SRC_SCREENUTILITY_H_
#define SRC_SCREENUTILITY_H_

#include <MappingStructs.h>
#include <iostream>

class ScreenUtility {
public:
    screen_point_t calculateAnyScreenPoint(percentage_point_t big_query_point) const;
    percentage_point_t calculateAnyScreenPercentage(screen_point_t big_query_point) const;

    const screen_point_t getPressedAt() const;
    void setPressedAt(const screen_point_t pressedAt);
    void moveOffset(double xDelta, double yDelta);
    const screen_size_t getAllocated() const;
    void setAllocated(const screen_size_t allocated);
    const screen_point_t getOffset() const;
    void setOffset(const screen_point_t origin);
    bool isRecenter() const;
    void setRecenter(bool recenter = true);
    const screen_size_t getBigMapPixelSize() const;
    screen_point_t getBigMapPixelCenter() const;


private:
    screen_point_t pressedAt;
    screen_point_t offset;
    screen_size_t allocated;
    bool recenter = true;

};

#endif /* SRC_SCREENUTILITY_H_ */
