/*
 * CapstoneMapping.h
 *
 *  Created on: Apr 27, 2020
 *      Author: roseba
 */

#ifndef SRC_CAPSTONEMAPPING_H_
#define SRC_CAPSTONEMAPPING_H_
#include <iostream>
#include <gtkmm.h>

class CapstoneMapping {
public:
    CapstoneMapping();
    CapstoneMapping(double w, double h);
    ~CapstoneMapping();

    const Cairo::RefPtr<Cairo::Surface>& getMappingSurface() const;
    Cairo::RefPtr<Cairo::Surface> createBigMap();
    float getCenterLatitude() const;
    void setCenterLatitude(float centerLatitude );
    float getCenterLongitude() const;
    void setCenterLongitude(float centerLongitude );
    double getHeight() const;
    double getWidth() const;

private:
    Cairo::RefPtr<Cairo::Surface> mapping_surface;
    double width;
    double height;
    float center_latitude =91.0;
    float center_longitude = 181.0;
};

#endif /* SRC_CAPSTONEMAPPING_H_ */
