/*
 * MappingCairoDrawer.cpp
 *
 *  Created on: May 18, 2020
 *      Author: roseba
 */

#include "MappingCairoDrawer.h"

MappingCairoDrawer::~MappingCairoDrawer()
{
    // TODO Auto-generated destructor stub
}

MappingCairoDrawer::MappingCairoDrawer(Cairo::RefPtr<Cairo::Surface> mapp_surface,
                                                                                std::shared_ptr<LatLonUtility> lat_utility,
                                                                                std::shared_ptr<ScreenUtility> scre_utility):mapping_surface(mapp_surface),
                                                                                                                                                    latlon_utility(lat_utility),
                                                                                                                                                    screen_utility(scre_utility)
{
}

void MappingCairoDrawer::drawGrid()
{

    int pixel_width = screen_utility->getBigMapPixelSize().width;
    int pixel_height = screen_utility->getBigMapPixelSize().height;
    int i;
    int grid_incr = pixel_width/3;
    Cairo::RefPtr<Cairo::Context> context = Cairo::Context::create(mapping_surface);
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
}

void MappingCairoDrawer::drawNode(NodeStruct node)
{
    latlon_point_t origin = latlon_utility->getBigMapLatlonOrigin();
    //std::cout <<  origin.latitude<<" "<<origin.longitude<<" _ "<<node.point.latitude<<" "<<node.point.longitude  <<std::endl;
    latlon_point_t  diff(double(std::abs( origin.latitude) - std::abs( node.point.latitude )),
                                    double( std::abs(origin.longitude ) - std::abs(node.point.longitude) ));
//    std::cout <<diff.latitude<<" "<<diff.longitude    <<std::endl;
    screen_point_t screen = screen_utility->calculateAnyScreenPoint(diff);
//    std::cout << screen.X <<" "<<screen.Y<<std::endl;
//    std::cout <<std::endl;
    Cairo::RefPtr<Cairo::Context> context = Cairo::Context::create(mapping_surface);

    context ->set_line_width(2.0);
    context->set_source_rgba( 0.0, 0.0, 1.0, 1.0);
    context->arc(screen.X, screen.Y, 5.0, 0.0, 2.0*M_PI);
    context ->stroke();

}

const Cairo::RefPtr<Cairo::Surface>& MappingCairoDrawer::getMappingSurface() const
{
    return mapping_surface;
}

void MappingCairoDrawer::setMappingSurface(const Cairo::RefPtr<Cairo::Surface> &mappingSurface)
{
    mapping_surface = mappingSurface;
}
