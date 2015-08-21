#include "SinglePanel.h"

SinglePanel::SinglePanel(const Glib::ustring& startDirPath) {
    Gtk::TreeView *filesTreeView = createFilesTreeView();
    this->add(*filesTreeView);

    Gtk::Label *bottomStatusBar = new Gtk::Label(startDirPath);

    this->pack_end(*bottomStatusBar, Gtk::PackOptions::PACK_SHRINK);
}

Gtk::TreeView* SinglePanel::createFilesTreeView() {
    return Gtk::manage(new Gtk::TreeView());
}
