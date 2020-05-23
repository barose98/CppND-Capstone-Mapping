/*
 * CapstoneDrawingArea.cpp
 *
 *  Created on: May 22, 2020
 *      Author: roseba
 */

#include "CapstoneDrawingArea.h"

CapstoneDrawingArea::CapstoneDrawingArea()
{
    this->add_events(Gdk::EventMask( GDK_STRUCTURE_MASK | GDK_POINTER_MOTION_MASK |  GDK_BUTTON_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK ));
    capstone_mapping =  std::make_unique<CapstoneMapping>();
}

CapstoneDrawingArea::CapstoneDrawingArea(const Gtk::DrawingArea &other)
{
    std::cout <<  "CDA Copy Constructor"  <<std::endl;
    this->set_events(other.get_events());
}

CapstoneDrawingArea CapstoneDrawingArea::operator =(const Gtk::DrawingArea &other)
{
    std::cout <<  "CDA Copy Assignment Constructor"  <<std::endl;
}

CapstoneDrawingArea::~CapstoneDrawingArea()
{
    // TODO Auto-generated destructor stub
}


void CapstoneDrawingArea::initalize(latlon_point_t big_map_center)
{
    this->set_visible(true);
    this->set_can_focus(true);

    capstone_mapping->latlon_utility->setBigMapLatlonCenter(big_map_center);

    capstone_mapping->createBigMap();
}

bool CapstoneDrawingArea::on_motion_notify_event(GdkEventMotion *motion_event)
{
    if(motion_event->state & GDK_BUTTON1_MASK){
        capstone_mapping->screen_utility->moveOffset(motion_event->x, motion_event->y);
            //capstone_mapping->screen_utility->setBigMapPixelCenter(screen_point_t( capstone_mapping->screen_utility->getOffset().X + capstone_mapping->screen_utility->getAllocated().width/2.0,  capstone_mapping->screen_utility->getOffset().Y +capstone_mapping->screen_utility->getAllocated().height/2.0  )  );
            this->queue_draw();

    }else{
        std::stringstream ss;
        screen_point_t bigMapMoved;
        bigMapMoved.X = capstone_mapping->screen_utility->getOffset().X +motion_event->x;
        bigMapMoved.Y = capstone_mapping->screen_utility->getOffset().Y +motion_event->y;
        percentage_point_t percent = capstone_mapping->screen_utility->calculateAnyScreenPercentage(bigMapMoved);
        latlon_point_t current = capstone_mapping->latlon_utility->calculateAnyLatLonPoint(percent);
        ss<<current.latitude<<" "<<current.longitude;
        this->set_tooltip_text(ss.str().c_str());
    }
    screen_point_t pressedAt;
    pressedAt.X = motion_event->x;
    pressedAt.Y = motion_event->y;
    capstone_mapping->screen_utility->setPressedAt(pressedAt);
    return true;
}

bool CapstoneDrawingArea::on_button_press_event(GdkEventButton *button_event)
{
     screen_point_t pressedAt;
      pressedAt.X = button_event->x;
      pressedAt.Y = button_event->y;
      capstone_mapping->screen_utility->setPressedAt(pressedAt);

      return true;
}

bool CapstoneDrawingArea::on_button_release_event(GdkEventButton *release_event)
{
    screen_point_t bigMapReleased;
    bigMapReleased.X = capstone_mapping->screen_utility->getOffset().X +release_event->x;
    bigMapReleased.Y = capstone_mapping->screen_utility->getOffset().Y +release_event->y;
    percentage_point_t percent = capstone_mapping->screen_utility->calculateAnyScreenPercentage(bigMapReleased);
    latlon_point_t current_latlon_center = capstone_mapping->latlon_utility->calculateAnyLatLonPoint(percent);
    capstone_mapping->latlon_utility->setLittleMapLatlonCenter(current_latlon_center);
    std::cout << current_latlon_center.latitude<<" "<<current_latlon_center.longitude   <<std::endl;

    return true;
}


bool CapstoneDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    screen_size_t allocated;
    allocated.width = this->get_allocated_width();
    allocated.height= this->get_allocated_height();
    capstone_mapping->screen_utility->setAllocated(allocated);
    if(capstone_mapping->screen_utility->isRecenter()){
        screen_point_t offset;
        screen_size_t  big_map_pixel_size = capstone_mapping->screen_utility->getBigMapPixelSize();
        offset.X = big_map_pixel_size.width/2.0-capstone_mapping->screen_utility->getAllocated().width/2;
        offset.Y = big_map_pixel_size.height/2.0-capstone_mapping->screen_utility->getAllocated().height/2;
        capstone_mapping->screen_utility->setOffset(offset);
        capstone_mapping->screen_utility->setRecenter(false);
    }
    Cairo::RefPtr<Cairo::Surface> little_surface;
    little_surface = Cairo::Surface::create(capstone_mapping->getMappingSurface(), capstone_mapping->screen_utility->getOffset().X, capstone_mapping->screen_utility->getOffset().Y, double(allocated.width), double(allocated.height));
    cr->set_source( little_surface, double(0), double(0));
    cr->paint();
    return false;
}
