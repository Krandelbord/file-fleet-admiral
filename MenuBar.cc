#include "MenuBar.h"
#include "config.h"
using namespace Gtk::Menu_Helpers;

MenuBar::MenuBar() {
    this->append(*createFileMenu());
    this->append(*createHelpMenu());
}

Gtk::MenuItem* MenuBar::createFileMenu() {
    Gtk::MenuItem* fileMenu = Gtk::manage(new Gtk::MenuItem(_("_File"), true));
    Gtk::Menu* submenu1 = Gtk::manage(new Gtk::Menu);
    Gtk::MenuItem* addDirMenuItem = Gtk::manage(new Gtk::MenuItem(_("Add directory")));
    submenu1->append(*addDirMenuItem);
    fileMenu->set_submenu(*submenu1);

    return fileMenu;
}

Gtk::MenuItem* MenuBar::createHelpMenu() {
    Gtk::MenuItem* item2 = Gtk::manage(new Gtk::MenuItem("Help"));
    Gtk::Menu* submenu2 = Gtk::manage(new Gtk::Menu);
    Gtk::MenuItem* subitem2 = Gtk::manage(new Gtk::MenuItem("About"));
    submenu2->append(*subitem2);
    item2->set_submenu(*submenu2);

    return item2;
}

void MenuBar::onQuitMenuItem() {
        Gtk::Main::quit();
}

