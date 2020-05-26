/*
 * MappingCairoDrawer.cpp
 *
 *  Created on: May 18, 2020
 *      Author: Barrett Rose
 */

#include <CairoDrawer.h>

CairoDrawer::~CairoDrawer()
{
    //
}

CairoDrawer::CairoDrawer(Cairo::RefPtr<Cairo::Surface> mapp_surface,
                                                                                std::shared_ptr<LatLonUtility> lat_utility,
                                                                                std::shared_ptr<ScreenUtility> scre_utility):mapping_surface(mapp_surface),
                                                                                                                                                    latlon_utility(lat_utility),
                                                                                                                                                    screen_utility(scre_utility)
{
}

void CairoDrawer::drawGrid()
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

}

void CairoDrawer::drawNode(NodeStruct node)
{
    percentage_point_t percent = latlon_utility->calculateAnyLatLonPercentage(node.point);
    screen_point_t screen = screen_utility->calculateAnyScreenPoint(percent);
//    std::cout << screen.X <<" "<<screen.Y<<std::endl;
    Cairo::RefPtr<Cairo::Context> context = Cairo::Context::create(mapping_surface);

    context ->set_line_width(2.0);
    context->set_source_rgba( 0.0, 0.0, 1.0, 1.0);
    context->arc(screen.X, screen.Y, 3.0, 0.0, 2.0*M_PI);
    context ->stroke();

}

const Cairo::RefPtr<Cairo::Surface>& CairoDrawer::getMappingSurface() const
{
    return mapping_surface;
}

void CairoDrawer::drawWay(WayStruct &way)
{
    std::string front = way.nds.front();
    NodeStruct found = *(std::find_if(nodes.begin(), nodes.end(), [front](NodeStruct other){return front == other.id;  }  )  );


    Cairo::RefPtr<Cairo::Context> context = Cairo::Context::create(mapping_surface);
    context ->set_line_width(2.0);

    setColor(context, way);
    percentage_point_t percent = latlon_utility->calculateAnyLatLonPercentage(found.point);
    screen_point_t screen = screen_utility->calculateAnyScreenPoint(percent);
    context->move_to(screen.X, screen.Y);
    for(int i = 1; i<way.nds.size();++i){
        found = *(std::find_if(nodes.begin(), nodes.end(), [i, way](NodeStruct other){return way.nds.at(i) == other.id;  }  )  );
        percent = latlon_utility->calculateAnyLatLonPercentage(found.point);
        screen = screen_utility->calculateAnyScreenPoint(percent);
        context->line_to(screen.X, screen.Y);
    }
    if(!way.isBuilding && !way.isWater){
        context ->stroke();
    }else{
        context->close_path();
        context->fill();
    }

}

void CairoDrawer::setColor(Cairo::RefPtr<Cairo::Context> &context, WayStruct &way)
{
    if(!way.waterway.empty() ){
        context->set_source_rgba( 0.0, 0.5, 1.0, 1.0);
    }else if(!way.highway.empty()){
       if(way.highway == "footway" || way.highway == "path"){
            context->set_source_rgba( 1.0, 0.0, 0.0, 1.0);
            std::vector<double> dash={10.0};
            context->set_dash(dash, 0.0);
            return;
        }
        context->set_source_rgba( 1.0, 1.0, 0.0, 1.0);

    }else{
        context->set_source_rgba( 1.0, 1.0, 1.0, 1.0);
    }
}

void CairoDrawer::setMappingSurface(const Cairo::RefPtr<Cairo::Surface> &mappingSurface)
{
    mapping_surface = mappingSurface;
}
