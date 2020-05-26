#include <iostream>
#include <sstream>
#include <memory>
#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include <MappingStructs.h>

#include "CapstoneDrawingArea.h"

Gtk::Window* main_window ;
Gtk::DrawingArea* map_area ;

int main (int argc, char **argv)
{
    latlon_point_t latlon_center;
    latlon_center.latitude=91;
    latlon_center.longitude=181;
    std::string enteredLatLon, enteredLat, enteredLon;

    while(latlon_center.latitude>90 || latlon_center.latitude<-90 || latlon_center.longitude>180 || latlon_center.longitude<-180){
        std::cout << "Enter the center latitude <space> longitude:  ";
        std::getline(std::cin, enteredLatLon);
        if(enteredLatLon.empty() )
        {
            enteredLat = "35.595";
            enteredLon = "-82.555";
        }else{
            std::stringstream(enteredLatLon)>>enteredLat>>enteredLon;
        }
        std::stringstream(enteredLat)>>latlon_center.latitude;
        std::stringstream(enteredLon)>>latlon_center.longitude;
    }

    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.capstone_mapping");
    Glib::RefPtr<Gtk::Builder>  refBuilder = Gtk::Builder::create();

    try    {
        refBuilder->add_from_file("./capstone-mapping.glade");
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
//        refBuilder->get_widget("map-area", map_area);
//        if(map_area)
//        {
//TODO: NEW DRAWING AREA
            CapstoneDrawingArea drawing_area;// = *map_area;
            drawing_area.initalize(latlon_center);
            main_window->add(drawing_area);
//        }//if map area

        app->run(*(main_window));
    }
    delete main_window;
//    capstone_mapping->getting_thread.detach();
//    capstone_mapping->parsing_thread.detach();
    return 0;
}
