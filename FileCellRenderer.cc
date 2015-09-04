#include "FileCellRenderer.h"

FileCellRenderer::FileCellRenderer() {

}
void FileCellRenderer::render_vfunc (const ::Cairo::RefPtr< ::Cairo::Context >& cr, Widget& widget, const Gdk::Rectangle& background_area, const Gdk::Rectangle& cell_area, CellRendererState flags) {
    
    CellRendererText::render_vfunc (cr, widget, background_area, cell_area, flags);
}

