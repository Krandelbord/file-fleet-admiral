#ifndef FILE_CELL_RENDERER_H
#define FILE_CELL_RENDERER_H

#include <gtkmm.h>
using namespace Gtk;

class FileCellRenderer : public Gtk::CellRendererText {
    public:
       FileCellRenderer(); 
    protected:
       void render_vfunc (const ::Cairo::RefPtr< ::Cairo::Context >& cr, Widget& widget, const Gdk::Rectangle& background_area, const Gdk::Rectangle& cell_area, CellRendererState flags);
};

#endif /** FILE_CELL_RENDERER_H **/
