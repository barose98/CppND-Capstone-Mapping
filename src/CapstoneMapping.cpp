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
    std::cout << "Constructing CapstoneMapping. empty " <<this  <<std::endl;

    latlon_utility =  std::make_shared<LatLonUtility>();
    screen_utility =  std::make_shared<ScreenUtility>();

    this->downloader =  std::make_unique< OSMDownloader>(downloading_queue);
    this->parser =  std::make_unique< OSMDataParser>( downloading_queue, drawing_queue);
    this->drawer =  std::make_shared< CairoDrawer>(mapping_surface, latlon_utility, screen_utility);
    //mapping_surface->write_to_png("grid.png");
}


CapstoneMapping::~CapstoneMapping()
{
    std::cout <<"capstone mapping destr "<< this   <<std::endl;
//    std::cout <<  int(getting_future.wait_for(std::chrono_literals::operator ""ms(0)) )  <<  (parsing_status ==std::future_status::timeout) <<std::endl;
}
const Cairo::RefPtr<Cairo::Surface>& CapstoneMapping::getMappingSurface() const
{
    return mapping_surface;
}

void CapstoneMapping::createBigMap()
{
    bounding_box_t bbox(latlon_utility->calculateBigMapLatlonOrigin(), latlon_utility->getBigMapLatlonEdge());

    getting_future = std::async(std::launch::async, &OSMDownloader::downloadOSMap, *(this->downloader.get()), bbox  );
    std::cout << getting_future.get()   <<std::endl;

    double pixel_width = this->screen_utility->getBigMapPixelSize().width;
    double pixel_height= this->screen_utility->getBigMapPixelSize().height;

    mapping_surface = Cairo::RefPtr<Cairo::Surface>(new Cairo::Surface(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, pixel_width, pixel_height) )  );
    Cairo::RefPtr<Cairo::Context> context = Cairo::Context::create(mapping_surface);
    this->drawer->setMappingSurface(mapping_surface);

    context ->set_line_width(2.0);
    context->set_source_rgba( 1.0, 0.0, 0.0, 1.0);
    context ->arc(this->screen_utility->getBigMapPixelCenter().X,this->screen_utility->getBigMapPixelCenter().Y,25.0,0.0,2.0*M_PI);
    context ->stroke();

    //Outside box.
    context->set_line_width( 26.0);
    context->rectangle( 0.0, 0.0, pixel_width, pixel_height);
    std::vector<double> dash={2.0, 8.0};
    context->set_dash(dash, 0.0);
    context ->stroke();

    parsing_future = std::async(std::launch::async, &OSMDataParser::receiveOSMXML, *(this->parser.get()), drawer  );

}


