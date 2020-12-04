#include "RenamePopup.h"
#include "../config.h"

RenamePopup::RenamePopup(Gtk::Window &parent, Glib::ustring &renamePath) : Gtk::Dialog(_("Rename Window"), parent) {
    this->set_default_size(100, 100);
    label.set_label(renamePath);
    this->set_modal(false);
    this->get_vbox()->pack_start(label, Gtk::PackOptions::PACK_SHRINK);
    this->get_vbox()->pack_start(newFileName, Gtk::PackOptions::PACK_SHRINK);
    this->show_all_children();
}