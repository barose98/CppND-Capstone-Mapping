#include <iostream>
#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include <cairo-svg.h>
 
#include "CapstoneMapping.h"
bool on_map_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr);
bool on_map_moved(GdkEventMotion* motion_event);

Gtk::Window* main_window = nullptr;
Gtk::DrawingArea* map_area = nullptr;
const double big_map_size = 2500.0;
CapstoneMapping capstone_map(big_map_size,big_map_size);
Cairo::RefPtr<Cairo::Surface> little_surface;

double pressedAtX = 0.0;
double pressedAtY = 0.0;
double translateX = 0.0;
double translateY = 0.0;
double originX = 0.0;
double originY = 0.0;

int main (int argc, char **argv)
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.capstone_mapping");
  Glib::RefPtr<Gtk::Builder>  refBuilder = Gtk::Builder::create();

  try
  {
    refBuilder->add_from_file("../capstone-mapping.glade");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Gtk::BuilderError& ex)
  {
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
      map_area->signal_button_press_event().connect(
              [] (GdkEventButton* button_event)->bool{
                      pressedAtX = button_event->x;
                      pressedAtY = button_event->y;
                      translateX = 0.0;
                      translateY = 0.0;
                      return true;
      }      );

      map_area->signal_draw().connect(
              sigc::ptr_fun(on_map_draw      )//ptr fun
      );//connect
    }//if map area

    app->run(*main_window);
  }
  delete main_window;

  return 0;
}
bool on_map_moved(GdkEventMotion* motion_event)
{
    if(motion_event->state & GDK_BUTTON1_MASK){
    translateX =  (motion_event->x - pressedAtX)*-1.0;
    translateY = (motion_event->y - pressedAtY)*-1.0;
    if(map_area)
        map_area->queue_draw();
    }
    pressedAtX = motion_event->x;
    pressedAtY = motion_event->y;
    return true;
}
bool on_map_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr){
    const int width = map_area->get_allocated_width();
    const int height = map_area->get_allocated_height();
    originX += translateX;
    originY += translateY;
    if(originX < 0)
        originX =0;
    if(originY < 0)
         originY =0;
    double edgeX = big_map_size - width;
    double edgeY = big_map_size - height;
    if(originX > edgeX)
        originX = edgeX;
    if(originY > edgeY)
         originY = edgeY;
     little_surface = Cairo::Surface::create(capstone_map.getMappingSurface(), originX, originY, double(width), double(height));
    cr->set_source( little_surface, double(0), double(0));
    cr->paint();
    return false;
}
