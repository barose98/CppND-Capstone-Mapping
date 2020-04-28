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
    CapstoneMapping(double w, double h);
    ~CapstoneMapping();

    const Cairo::RefPtr<Cairo::Surface>& getMappingSurface() const
    {
        return mapping_surface;
    }
    Cairo::RefPtr<Cairo::Surface> createBigMap();

private:

    Cairo::RefPtr<Cairo::Surface> mapping_surface;
    double width;
    double height;
};

#endif /* SRC_CAPSTONEMAPPING_H_ */
