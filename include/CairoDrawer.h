/*
 * MappingCairoDrawer.h
 *
 *  Created on: May 18, 2020
 *      Author: Barrett Rose
 */

#ifndef SRC_MAPPINGCAIRODRAWER_H_
#define SRC_MAPPINGCAIRODRAWER_H_
/**
This class is used by the OSMDataParser class to draw the ways.
It holds references not only to the ways but also the nodes referred to by the ways.

It uses the LatLonUtility class to take the latitude and longitude in the OSM map
and the ScreenUtility class to figure out where on the Cairo surface the the particular
point on the particular way goes.
*/

#include <memory>
#include <algorithm>
#include <gtkmm.h>

#include "MappingStructs.h"
#include "ScreenUtility.h"
#include "LatLonUtility.h"
//#include "OSMDataParser.h"

class CairoDrawer {
public:
    CairoDrawer(
            Cairo::RefPtr<Cairo::Surface> mapping_surface,
            std::shared_ptr< LatLonUtility> latlon_utility ,
            std::shared_ptr< ScreenUtility> screen_utility
    );
    ~CairoDrawer();
    void drawCenter();
    void drawBorder();
    void drawGrid();
    void drawNode(NodeStruct node);
    void drawWay(WayStruct &&way);
    const Cairo::RefPtr<Cairo::Surface>& getMappingSurface() const;
    void setMappingSurface(const Cairo::RefPtr<Cairo::Surface> &mappingSurface);
    std::vector<NodeStruct> nodes;
    std::vector<WayStruct> ways;

private:
    void setColor( WayStruct &way);
    void setLineStyle( WayStruct &way);
    Cairo::RefPtr<Cairo::Surface> mapping_surface;
    Cairo::RefPtr<Cairo::Context> context;
    std::shared_ptr< LatLonUtility> latlon_utility ;
    std::shared_ptr< ScreenUtility> screen_utility ;
};

#endif /* SRC_MAPPINGCAIRODRAWER_H_ */
