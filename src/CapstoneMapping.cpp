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
    latlon_utility =  std::make_unique<CapstoneMappingUtility>();
    //mapping_surface =  this->createBigMap();

    this->downloader =  std::make_unique< OSMDownloader>();
    //mapping_surface->write_to_png("grid.png");
}

CapstoneMapping::CapstoneMapping(const CapstoneMapping &other)
{
    std::cout << "copy Constructing CapstoneMapping." <<this  <<std::endl;
    this->downloader =  std::make_unique< OSMDownloader>();


}

CapstoneMapping& CapstoneMapping::operator =(const CapstoneMapping &other)
{

    this->downloader =  std::make_unique< OSMDownloader>();

    return *this;
}
CapstoneMapping::~CapstoneMapping()
{
    // TODO Auto-generated destructor stub
    //this->mapping_surface = nullptr;
    std::cout <<"capstone mapping destr "<< this   <<std::endl;
}
const Cairo::RefPtr<Cairo::Surface>& CapstoneMapping::getMappingSurface() const
{
    return mapping_surface;
}

void CapstoneMapping::createBigMap()
{
    double pixel_width = this->latlon_utility->getMapPixelSize().w;
    double pixel_height= this->latlon_utility->getMapPixelSize().h;
    Cairo::RefPtr<Cairo::Surface> big_surface = Cairo::RefPtr<Cairo::Surface>(new Cairo::Surface(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, pixel_width, pixel_height) )  );
    Cairo::RefPtr<Cairo::Context> context = Cairo::Context::create(big_surface);
    // coordinates for the center of the window
    int i;
    int grid_incr = pixel_width/3;

    context ->set_line_width(2.0);
    context->set_source_rgba( 1.0, 0.0, 0.0, 1.0);
    context ->arc(this->latlon_utility->getMapPixelCenter().x,this->latlon_utility->getMapPixelCenter().y,25.0,0.0,6.28);
    context ->stroke();
    //Paint the background.
    context->set_source_rgba( 0.0, 0.0, 0.0, 0.1);
    context->paint();
    //Draw some horizontal lines.
    context->set_source_rgba( 0.0, 1.0, 0.0, 1.0);
    for(i=0;i<pixel_width;i+=grid_incr)
      {
        context->move_to( 0.0, double(i));
        context->line_to( pixel_width, double(i));
        context->stroke();
      }
    //Draw some vertical lines.
    for(i=0;i<pixel_height;i+= grid_incr)
      {
        context->move_to( double(i), 0.0);
        context->line_to(  double(i), pixel_height);
        context->stroke();
      }
    //Outside box.
    context->set_line_width( 16.0);
    context->set_source_rgba( 1.0, 0.0, 1.0, 1.0);
    context->rectangle( 0.0, 0.0, pixel_width, pixel_height);

    context ->stroke();

    bounding_box_t bbox(latlon_utility->getMapLatlonCenter(),latlon_utility->getMapLatlonEdge());
    std::cout << "Creating big surface.  "<< (this->downloader.get()  ) <<std::endl;
    this->downloader->downloadOSMap(bbox);
    this->mapping_surface = big_surface;
}


