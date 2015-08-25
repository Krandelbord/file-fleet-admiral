#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <gtkmm.h>
using namespace Gtk::Menu_Helpers;

class MenuBar : public Gtk::MenuBar {
    public :
        MenuBar();
    private:
        Gtk::MenuItem* createFileMenu();
        Gtk::MenuItem* createHelpMenu();
        void onQuitMenuItem();
};

#endif /** MENU_BAR_H */
