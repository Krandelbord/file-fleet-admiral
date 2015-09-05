#include "PanelHeader.h"

PanelHeader::PanelHeader(const Glib::ustring& labelTxt) {
    headerLabel.set_text(labelTxt);
    headerLabel.set_ellipsize(Pango::EllipsizeMode::ELLIPSIZE_MIDDLE);
    this->add(headerLabel);
    Gtk::Spinner* spinner = Gtk::manage(new Gtk::Spinner());
    this->add(*spinner);
}

void PanelHeader::setCurrentDir(const Glib::ustring& newDir) {
    headerLabel.set_text(newDir);
}
