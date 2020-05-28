/*
 * CapstoneDrawingArea.h
 *
 *  Created on: May 22, 2020
 *      Author: roseba
 */

#ifndef SRC_CAPSTONEDRAWINGAREA_H_
#define SRC_CAPSTONEDRAWINGAREA_H_
/**
 * This class subclasses GtkDrawlingArea and overrides three event handlers.
Additionally, it has an initialize method that starts the whole downloading and drawing process.
It also calls the timedRedraw method while the CairoDrawer is drawing, as this turns out to be a resource
intensive process and the user needs to be shown that the program is chewing on the drawing process and is not stuck.
*/

#include <gtkmm/drawingarea.h>
#include"CapstoneMapping.h"
#include"MappingStructs.h"
#include"OSMDownloadQueue.h"
#include"OSMDrawingQueue.h"

class CapstoneDrawingArea: public Gtk::DrawingArea {
public:
    CapstoneDrawingArea();
    ~CapstoneDrawingArea();
    void initalize(latlon_point_t big_latlon_center);

protected:
    virtual bool on_motion_notify_event(GdkEventMotion *motion_event) override;
    virtual bool on_button_press_event(GdkEventButton *button_event) override;
    virtual bool on_button_release_event(GdkEventButton *release_event) override;
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
    bool timedRedraw();

private:
    std::unique_ptr<CapstoneMapping> capstone_mapping ;
    std::shared_ptr<OSMDownloadQueue<std::string>> downloading_queue;
    std::shared_ptr<OSMDrawingQueue<bool>> drawing_queue;
};

#endif /* SRC_CAPSTONEDRAWINGAREA_H_ */
