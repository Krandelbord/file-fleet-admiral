#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <gtkmm.h>
using namespace Gtk::Menu_Helpers;

class MenuBar : public Gtk::MenuBar {
    public :
        MenuBar();
    private:
        Gtk::Menu* createFileMenu();
        Gtk::Menu* createHelpMenu();
        void onQuitMenuItem();
 
        sigc::signal<void> m_signal_create_dir;
        sigc::signal<void> m_signal_open_help;
};

#endif /** MENU_BAR_H */
