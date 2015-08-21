#include "MenuBar.h"
#include "config.h"
using namespace Gtk::Menu_Helpers;

MenuBar::MenuBar() {
        //this->prepend(MenuElem(_("_File"), *this->createFileMenu()));
        //this->prepend(MenuElem(_("_Help"), *this->createHelpMenu()));
        this->append(*new Gtk::MenuItem("File"));
}

Gtk::Menu *MenuBar::createFileMenu() {
        Gtk::Menu *file_menu = new Gtk::Menu();
        //file_menu->items().push_back( StockMenuElem(Gtk::Stock::OPEN, Gtk::AccelKey("<Control>O"), m_signal_create_dir) );

        //file_menu->items().push_back( StockMenuElem(Gtk::Stock::QUIT,  sigc::mem_fun(*this, &MenuBar::onQuitMenuItem) ) );
        return file_menu;
}

Gtk::Menu *MenuBar::createHelpMenu() {
     Gtk::Menu *help_menu = new Gtk::Menu();
     //help_menu->items().push_back( StockMenuElem(Gtk::Stock::OPEN, Gtk::AccelKey("<Control>O"), m_signal_open_help) );
     return help_menu;
}

void MenuBar::onQuitMenuItem() {
        Gtk::Main::quit();
}

