/*
 * CapstoneMapping.h
 *
 *  Created on: Apr 27, 2020
 *      Author: roseba
 */

#ifndef SRC_CAPSTONEMAPPING_H_
#define SRC_CAPSTONEMAPPING_H_
#include <iostream>
#include <memory>
#include <gtkmm.h>
#include "OSMDownloader.h"

class CapstoneMapping {
public:
    CapstoneMapping();
    CapstoneMapping(double w, double h);
    ~CapstoneMapping();
    CapstoneMapping(const CapstoneMapping& other);
    CapstoneMapping &operator=(const CapstoneMapping& other);


    const Cairo::RefPtr<Cairo::Surface>& getMappingSurface() const;
    Cairo::RefPtr<Cairo::Surface> createBigMap();
    std::unique_ptr< OSMDownloader> downloader;

    double getHeight() const;
    double getWidth() const;

private:
    Cairo::RefPtr<Cairo::Surface> mapping_surface;
    double width;
    double height;

};

#endif /* SRC_CAPSTONEMAPPING_H_ */
