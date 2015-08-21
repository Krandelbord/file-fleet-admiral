#include "MenuBar.h"
#include "config.h"
using namespace Gtk::Menu_Helpers;

MenuBar::MenuBar() {
    Gtk::MenuItem* item = Gtk::manage(new Gtk::MenuItem("test"));
    Gtk::Menu* submenu1 = Gtk::manage(new Gtk::Menu);
    Gtk::MenuItem* subitem1 = Gtk::manage(new Gtk::MenuItem("sub Item"));
    submenu1->append(*subitem1);
    item->set_submenu(*submenu1);
    Gtk::MenuItem* item2 = Gtk::manage(new Gtk::MenuItem("test2"));
    Gtk::Menu* submenu2 = Gtk::manage(new Gtk::Menu);
    Gtk::MenuItem* subitem2 = Gtk::manage(new Gtk::MenuItem("sub item 2"));
    submenu2->append(*subitem2);
    item2->set_submenu(*submenu2);

    this->append(*item);
    this->append(*item2);
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

