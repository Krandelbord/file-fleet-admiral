#include "SinglePanel.h"

SinglePanel::SinglePanel() {
    Gtk::TreeView *filesTreeView = createFilesTreeView();
    this->add(*filesTreeView);

    Gtk::Label *bottomStatusBar = new Gtk::Label("/home/emil");

    this->pack_end(*bottomStatusBar, Gtk::PackOptions::PACK_SHRINK);
}

Gtk::TreeView* SinglePanel::createFilesTreeView() {
    return Gtk::manage(new Gtk::TreeView());
}
