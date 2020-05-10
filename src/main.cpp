#include <iostream>
#include <sstream>
#include <memory>
#include <gtkmm.h>
#include <cairomm/cairomm.h>

#include "CapstoneMappingUtility.h"
#include "ScreenUtility.h"
#include"CapstoneMapping.h"

ScreenUtility screen_util;

Gtk::Window* main_window ;
Gtk::DrawingArea* map_area ;
std::unique_ptr<CapstoneMapping> capstone_mapping =  std::make_unique<CapstoneMapping>();

bool on_map_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr);
bool on_map_moved(GdkEventMotion* motion_event);

int main (int argc, char **argv)
{
    latlon_point_t latlon_center;
    latlon_center.latitude=91;
    latlon_center.longitude=181;
    std::string enteredLat, enteredLon;

    while(latlon_center.latitude>90 || latlon_center.latitude<-90 || latlon_center.longitude>180 || latlon_center.longitude<-180){
    std::cout << "Enter the center latitude <space> longitude:  ";
    std::cin>>enteredLat>>enteredLon;
    std::stringstream(enteredLat)>>latlon_center.latitude;
    std::stringstream(enteredLon)>>latlon_center.longitude;
    }
    capstone_mapping->latlon_utility->setMapLatlonCenter(latlon_center);
    capstone_mapping->createBigMap();
    std::cout <<  "finished creating"  <<std::endl;

    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.capstone_mapping");
    Glib::RefPtr<Gtk::Builder>  refBuilder = Gtk::Builder::create();

    try    {
        refBuilder->add_from_file("../capstone-mapping.glade");
    }
    catch(const Glib::FileError& ex)    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Glib::MarkupError& ex)    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Gtk::BuilderError& ex)    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }
    refBuilder->get_widget("mapping-window", main_window);
    if(main_window)
    {
        refBuilder->get_widget("map-area", map_area);
        if(map_area)
        {
            map_area->signal_motion_notify_event().connect( sigc::ptr_fun(on_map_moved) );
            map_area->signal_draw().connect(sigc::ptr_fun(on_map_draw )  );
            map_area->signal_button_press_event().connect(
                    [] (GdkEventButton* button_event)->bool{
                screen_point_t pressedAt;
                pressedAt.X = button_event->x;
                pressedAt.Y = button_event->y;
                screen_util.setPressedAt(pressedAt);

                return true;
            }      );
            map_area->signal_button_release_event().connect(
                    [] (GdkEventButton* button_event)->bool{
                latlon_point_t latlon_center = capstone_mapping->latlon_utility->calculateAnyLatLonPoint(capstone_mapping->latlon_utility->getMapPixelCenter(),  screen_util.getOrigin());
                std::cout << latlon_center.latitude<<" "<<latlon_center.longitude   <<std::endl;

                return true;
            }  );

        }//if map area
        app->run(*(main_window));
    }
    delete main_window;

    return 0;
}
bool on_map_moved(GdkEventMotion* motion_event)
{
    if(motion_event->state & GDK_BUTTON1_MASK){
        screen_util.moveOrigin(motion_event->x, motion_event->y);
        if(map_area){
            capstone_mapping->latlon_utility->setMapPixelCenter(screen_point_t( screen_util.getOrigin().X + screen_util.getAllocated().width/2.0,  screen_util.getOrigin().Y +screen_util.getAllocated().height/2.0  )  );
            map_area->queue_draw();
        }
    }else{
        std::stringstream ss;
        latlon_point_t current = capstone_mapping->latlon_utility->calculateAnyLatLonPoint(screen_point_t(motion_event->x , motion_event->y) , screen_util.getOrigin());
        ss<<current.latitude<<" "<<current.longitude;
        map_area->set_tooltip_text(ss.str().c_str());
    }
    screen_point_t pressedAt;
    pressedAt.X = motion_event->x;
    pressedAt.Y = motion_event->y;
    screen_util.setPressedAt(pressedAt);
    return true;
}
bool on_map_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr){
    screen_size_t allocated;
    allocated.width = map_area->get_allocated_width();
    allocated.height= map_area->get_allocated_height();
    screen_util.setAllocated(allocated);
    if(screen_util.isRecenter()){
        screen_point_t origin;
        screen_size_t  big_map_pixel_size = capstone_mapping->latlon_utility->getMapPixelSize();
        origin.X = big_map_pixel_size.width/2.0-screen_util.getAllocated().width/2;
        origin.Y = big_map_pixel_size.height/2.0-screen_util.getAllocated().height/2;
        screen_util.setOrigin(origin);
        screen_util.setRecenter(false);
    }
    Cairo::RefPtr<Cairo::Surface> little_surface;
    little_surface = Cairo::Surface::create(capstone_mapping->getMappingSurface(), screen_util.getOrigin().X, screen_util.getOrigin().Y, double(allocated.width), double(allocated.height));
    cr->set_source( little_surface, double(0), double(0));
    cr->paint();
    return false;
}
