#include "ToolBar.h"
#include "config.h"
#include "ChownWindow.h"

ToolBar::ToolBar() {   
    Gtk::ToolButton* toolItem = new Gtk::ToolButton("chown");
    toolItem->signal_clicked().connect(sigc::mem_fun(this, &ToolBar::onChownClicked));
    this->append(*toolItem);
}


void ToolBar::onChownClicked() {
    gfm_debug("chwon clicked\n");
    Gtk::Window *parent = dynamic_cast<Gtk::Window *>(this->get_toplevel());
    ChownWindow chownWin(static_cast<Gtk::Window&>(*parent));

    chownWin.get_vbox()->add(*new Gtk::Label("the chown window"));

    chownWin.show_all();
    chownWin.run();
}
