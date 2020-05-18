/*
 * MappingCairoDrawer.h
 *
 *  Created on: May 18, 2020
 *      Author: roseba
 */

#ifndef SRC_MAPPINGCAIRODRAWER_H_
#define SRC_MAPPINGCAIRODRAWER_H_

#include <memory>
#include <gtkmm.h>

#include "MappingStructs.h"
#include "ScreenUtility.h"
#include "LatLonUtility.h"
//#include "OSMDataParser.h"

class MappingCairoDrawer {
public:
    MappingCairoDrawer(
            Cairo::RefPtr<Cairo::Surface> mapping_surface,
            std::shared_ptr< LatLonUtility> latlon_utility ,
            std::shared_ptr< ScreenUtility> screen_utility
    );
    ~MappingCairoDrawer();
    void drawGrid();
    void drawNode(NodeStruct node);
    const Cairo::RefPtr<Cairo::Surface>& getMappingSurface() const;
    void setMappingSurface(const Cairo::RefPtr<Cairo::Surface> &mappingSurface);

private:
    Cairo::RefPtr<Cairo::Surface> mapping_surface;
    std::shared_ptr< LatLonUtility> latlon_utility ;
    std::shared_ptr< ScreenUtility> screen_utility ;
};

#endif /* SRC_MAPPINGCAIRODRAWER_H_ */
