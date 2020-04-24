#include <iostream>
#include <gtkmm.h>
//#include <glibmm.h>
#include <cairomm/cairomm.h>
#include <cairo-svg.h>

Gtk::Window* main_window = nullptr;
bool pressed =false;

bool on_map_moved(GdkEventMotion* motion_event)
{
    if(pressed)
    std::cout <<  "moved"  <<std::endl;
    return true;
}

int main (int argc, char **argv)
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.capstone_mapping");
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
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
    Gtk::DrawingArea* map_area= nullptr;
    refBuilder->get_widget("map-area", map_area);
    if(map_area)
    {
      map_area->signal_motion_notify_event().connect( sigc::ptr_fun(on_map_moved) );
      map_area->signal_button_press_event().connect(        [] (GdkEventButton* button_event)->bool{pressed = true;}      );
      map_area->signal_button_release_event().connect(     [](GdkEventButton* button_event)->bool{pressed = false;}     );
    }

    app->run(*main_window);
  }

  delete main_window;

  return 0;
}
