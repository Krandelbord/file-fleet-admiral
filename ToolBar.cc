#include "ToolBar.h"

ToolBar::ToolBar() {   
    Gtk::ToolButton* toolItem = new Gtk::ToolButton("chown");
    this->append(*toolItem);
}
