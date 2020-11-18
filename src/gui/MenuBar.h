#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <gtkmm.h>
using namespace Gtk::Menu_Helpers;

class MenuBar : public Gtk::MenuBar {
    public :
        MenuBar(Gtk::Window* parentWindow);
    private:
        Gtk::MenuItem* createFileMenu(Gtk::Window* parentWindow);
        Gtk::MenuItem* createHelpMenu();
        Gtk::MenuItem* createFilePanelMenu(Glib::ustring string);

        void onQuitMenuItem();
        void onShowSettings(Gtk::Window* parentWindow);
};

#endif /** MENU_BAR_H */
