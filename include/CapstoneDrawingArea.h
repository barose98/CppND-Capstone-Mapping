/*
 * CapstoneDrawingArea.h
 *
 *  Created on: May 22, 2020
 *      Author: roseba
 */

#ifndef SRC_CAPSTONEDRAWINGAREA_H_
#define SRC_CAPSTONEDRAWINGAREA_H_

#include <gtkmm/drawingarea.h>
#include"CapstoneMapping.h"
#include"MappingStructs.h"

class CapstoneDrawingArea: public Gtk::DrawingArea {
public:
    CapstoneDrawingArea();
    CapstoneDrawingArea(const Gtk::DrawingArea &other);
    CapstoneDrawingArea operator=(const Gtk::DrawingArea &other);
    ~CapstoneDrawingArea();
    void initalize(latlon_point_t big_latlon_center);

protected:
    virtual bool on_motion_notify_event(GdkEventMotion *motion_event);
    virtual bool on_button_press_event(GdkEventButton *button_event) override;
    virtual bool on_button_release_event(GdkEventButton *release_event) override;
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

private:
//    bool on_map_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr);
//    bool on_map_moved(GdkEventMotion* motion_event);
    std::unique_ptr<CapstoneMapping> capstone_mapping ;
};

#endif /* SRC_CAPSTONEDRAWINGAREA_H_ */
