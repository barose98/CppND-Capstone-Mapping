/*
 * CapstoneMapping.cpp
 *
 *  Created on: Apr 27, 2020
 *      Author: roseba
 */

#include "CapstoneMapping.h"

CapstoneMapping::CapstoneMapping(double w, double h): width(w), height(h)
{
    // TODO Auto-generated constructor stub
    std::cout << "Constructing big surface."   <<std::endl;
    mapping_surface =  this->createBigMap();
    //mapping_surface->write_to_png("grid.png");
}

CapstoneMapping::~CapstoneMapping()
{
    // TODO Auto-generated destructor stub
    //this->mapping_surface = nullptr;
}

Cairo::RefPtr<Cairo::Surface> CapstoneMapping::createBigMap()
{
    Cairo::RefPtr<Cairo::Surface> big_surface = Cairo::RefPtr<Cairo::Surface>(new Cairo::Surface(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height) )  );
    Cairo::RefPtr<Cairo::Context> context = Cairo::Context::create(big_surface);
    // coordinates for the center of the window
    int i;
    context ->set_line_width(2.0);
    context ->move_to(0, 0);

    //Paint the background.
    context->set_source_rgba( 0.0, 0.0, 0.0, 0.1);
    context->paint();
    //Draw some horizontal lines.
    context->set_source_rgba( 0.0, 1.0, 0.0, 1.0);
    for(i=0;i<width;i+=100)
      {
        context->move_to( 0.0, double(i));
        context->line_to( width, double(i));
        context->stroke();
      }
    //Draw some vertical lines.
    for(i=0;i<height;i+=100)
      {
        context->move_to( double(i), 0.0);
        context->line_to(  double(i), height);
        context->stroke();
      }
    //Outside box.
    context->set_line_width( 16.0);
    context->set_source_rgba( 1.0, 0.0, 1.0, 1.0);
    context->rectangle( 0.0, 0.0, width, height);

    context ->stroke();
    std::cout << "Creating big surface."   <<std::endl;
    return big_surface;
}
