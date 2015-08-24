#include "ToolBar.h"
#include "config.h"

ToolBar::ToolBar() {   
    Gtk::ToolButton* toolItem = new Gtk::ToolButton("chown");
    toolItem->signal_clicked().connect(sigc::mem_fun(this, &ToolBar::onChownClicked));
    this->append(*toolItem);
}


void ToolBar::onChownClicked() {
    gfm_debug("chwon clicked\n");
}
