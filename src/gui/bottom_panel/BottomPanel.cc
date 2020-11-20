#include <gtkmm/button.h>
#include "BottomPanel.h"

BottomPanel::BottomPanel() {
    this->set_hexpand(false);
    this->set_hexpand_set(false);
    this->add(*Gtk::manage(new Gtk::Button("F1 Help")));
    this->add(*Gtk::manage(new Gtk::Button("F2 Menu")));
    this->add(*Gtk::manage(new Gtk::Button("F3 View")));
    this->add(*Gtk::manage(new Gtk::Button("F4 Edit")));
    this->add(*Gtk::manage(new Gtk::Button("F5 Copy")));
    this->add(*Gtk::manage(new Gtk::Button("F6 Move")));
    this->add(*Gtk::manage(new Gtk::Button("F7 CreateDir")));
    this->add(*Gtk::manage(new Gtk::Button("F8 Delete")));
    this->add(*Gtk::manage(new Gtk::Button("F9 TopMenu")));
    this->add(*Gtk::manage(new Gtk::Button("F10 End")));
};