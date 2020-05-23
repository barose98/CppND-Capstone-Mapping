/*
 * MappingCairoDrawer.h
 *
 *  Created on: May 18, 2020
 *      Author: Barrett Rose
 */

#ifndef SRC_MAPPINGCAIRODRAWER_H_
#define SRC_MAPPINGCAIRODRAWER_H_

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
    void setColor(Cairo::RefPtr<Cairo::Context> &context,  WayStruct &way);
    void drawGrid();
    void drawNode(NodeStruct node);
    void drawWay(WayStruct &way);
    const Cairo::RefPtr<Cairo::Surface>& getMappingSurface() const;
    void setMappingSurface(const Cairo::RefPtr<Cairo::Surface> &mappingSurface);
    std::vector<NodeStruct> nodes;
    std::vector<WayStruct> ways;

private:
    Cairo::RefPtr<Cairo::Surface> mapping_surface;
    std::shared_ptr< LatLonUtility> latlon_utility ;
    std::shared_ptr< ScreenUtility> screen_utility ;
};

#endif /* SRC_MAPPINGCAIRODRAWER_H_ */
