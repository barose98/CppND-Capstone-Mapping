/*
 * CapstoneMapping.cpp
 *
 *  Created on: Apr 27, 2020
 *      Author: Barrett Rose
 */

#include "CapstoneMapping.h"

CapstoneMapping::CapstoneMapping(std::shared_ptr<OSMDownloadQueue<std::string>> queue, std::shared_ptr<OSMDrawingQueue<bool>> draw_queue)
:downloading_queue(queue),drawing_queue(draw_queue)
{
//    std::cout << "CapstoneMapping Constructor "<<this  <<std::endl;
    latlon_utility =  std::make_shared<LatLonUtility>();
    screen_utility =  std::make_shared<ScreenUtility>();
    this->drawer =  std::make_shared< CairoDrawer>(mapping_surface, latlon_utility, screen_utility);
    //mapping_surface->write_to_png("grid.png");
}

CapstoneMapping::~CapstoneMapping()
{

}
const Cairo::RefPtr<Cairo::Surface>& CapstoneMapping::getMappingSurface() const
{
    return mapping_surface;
}

void CapstoneMapping::createBigMap()
{
    bounding_box_t bbox(latlon_utility->calculateBigMapLatlonOrigin(), latlon_utility->getBigMapLatlonEdge());
    OSMDownloader downloader(downloading_queue);
    getting_future = std::async(std::launch::async, &OSMDownloader::downloadOSMap, std::move(downloader), bbox  );

    double pixel_width = this->screen_utility->getBigMapPixelSize().width;
    double pixel_height= this->screen_utility->getBigMapPixelSize().height;

    mapping_surface = Cairo::RefPtr<Cairo::Surface>(new Cairo::Surface(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, pixel_width, pixel_height) )  );
    this->drawer->setMappingSurface(mapping_surface);

    OSMDataParser parser( downloading_queue, drawing_queue);
    parsing_future = std::async(std::launch::async, &OSMDataParser::receiveOSMXML, std::move(parser), drawer  );
}


