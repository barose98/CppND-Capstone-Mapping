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
#include "ScreenLatLonUtility.h"

class CapstoneMapping {
public:
    CapstoneMapping();
    ~CapstoneMapping();
    CapstoneMapping(const CapstoneMapping& other);
    CapstoneMapping &operator=(const CapstoneMapping& other);

    const Cairo::RefPtr<Cairo::Surface>& getMappingSurface() const;
    Cairo::RefPtr<Cairo::Surface> createBigMap();

    std::unique_ptr< ScreenLatLonUtility > latlon_utility ;

private:
    std::unique_ptr< OSMDownloader> downloader;
    Cairo::RefPtr<Cairo::Surface> mapping_surface;


};

#endif /* SRC_CAPSTONEMAPPING_H_ */
