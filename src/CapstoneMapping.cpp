/*
 * CapstoneMapping.cpp
 *
 *  Created on: Apr 27, 2020
 *      Author: roseba
 */

#include "CapstoneMapping.h"

CapstoneMapping::CapstoneMapping()
{
    std::cout << "Constructing CapstoneMapping. empty " <<this  <<std::endl;

    latlon_utility =  std::make_shared<LatLonUtility>();
    screen_utility =  std::make_shared<ScreenUtility>();
    this->mapping_queue = std::make_shared<CapstoneMappingQueue<std::string>>();
    this->downloader =  std::make_unique< OSMDownloader>(mapping_queue);
    this->parser =  std::make_unique< OSMDataParser>( mapping_queue);
    this->drawer =  std::make_shared< MappingCairoDrawer>(mapping_surface, latlon_utility, screen_utility);
    //mapping_surface->write_to_png("grid.png");
}


CapstoneMapping::~CapstoneMapping()
{
    //this->mapping_surface = nullptr;
    std::cout <<"capstone mapping destr "<< this   <<std::endl;
}
const Cairo::RefPtr<Cairo::Surface>& CapstoneMapping::getMappingSurface() const
{
    return mapping_surface;
}

void CapstoneMapping::createBigMap()
{
    bounding_box_t bbox(latlon_utility->getBigMapLatlonOrigin(),latlon_utility->getBigMapLatlonEdge());
    getting_thread = std::thread([this,  bbox](){this->downloader->downloadOSMap(bbox); } );
//    std::future<std::string> getting_future = std::async(std::launch::async, &OSMDownloader::downloadOSMap,  *(downloader.get())  , bbox  );

    double pixel_width = this->screen_utility->getBigMapPixelSize().width;
    double pixel_height= this->screen_utility->getBigMapPixelSize().height;

    mapping_surface = Cairo::RefPtr<Cairo::Surface>(new Cairo::Surface(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, pixel_width, pixel_height) )  );
    Cairo::RefPtr<Cairo::Context> context = Cairo::Context::create(mapping_surface);
    std::cout << "Creating big surface.  "<<mapping_surface.refcount_() <<std::endl;

    this->drawer->setMappingSurface(mapping_surface);

    context ->set_line_width(2.0);
    context->set_source_rgba( 1.0, 0.0, 0.0, 1.0);
    context ->arc(this->screen_utility->getBigMapPixelCenter().X,this->screen_utility->getBigMapPixelCenter().Y,25.0,0.0,2.0*M_PI);
    context ->stroke();

    parsing_thread = std::thread([this](){this->parser->receiveOSMXML(this->drawer) ; } );
    std::cout <<  "finished drawing"  <<std::endl;

}


void CapstoneMapping::setInitialBigMapLatlonCenter(latlon_point_t bigMapLatlonCenter)
{
//    Store the LatLon origin here.
    latlon_point_t origin;
    origin.latitude = bigMapLatlonCenter.latitude - latlon_utility->getBigMapLatlonEdge()/2;
    origin.longitude = bigMapLatlonCenter.longitude - latlon_utility->getBigMapLatlonEdge()/2;
    latlon_utility->setBigMapLatlonOrigin(origin);
}
