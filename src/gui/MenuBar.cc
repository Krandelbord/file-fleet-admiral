#include "MenuBar.h"
#include "SettingsWindow.h"
#include "../config.h"

using namespace Gtk::Menu_Helpers;

MenuBar::MenuBar(Gtk::Window* parentWindow) {
    this->append(*createFilePanelMenu(_("_Left")));

    this->append(*createFileMenu(parentWindow));
    this->append(*createHelpMenu());

    this->append(*createFilePanelMenu(_("_Right")));
}

Gtk::MenuItem* MenuBar::createFileMenu(Gtk::Window* parentWindow) {
    Gtk::MenuItem* fileMenu = Gtk::manage(new Gtk::MenuItem(_("_File"), true));

    Gtk::Menu* submenu1 = Gtk::manage(new Gtk::Menu);
    fileMenu->set_submenu(*submenu1);
    
    submenu1->append(*Gtk::manage(new Gtk::MenuItem(_("Add _directory"), true)));
    
    Gtk::MenuItem* settingsMenu = Gtk::manage(new Gtk::MenuItem(_("_Preferences"), true));
    settingsMenu->signal_activate().connect(sigc::bind(sigc::mem_fun(*this, &MenuBar::onShowSettings), parentWindow));
    submenu1->append(*settingsMenu);

    Gtk::MenuItem* quitMenuItem = Gtk::manage(new Gtk::MenuItem(_("_Quit"), true));
    submenu1->append(*quitMenuItem);
    quitMenuItem->signal_activate().connect(sigc::mem_fun(*this, &MenuBar::onQuitMenuItem));

    return fileMenu;
}

Gtk::MenuItem* MenuBar::createHelpMenu() {
    Gtk::MenuItem*rootHelpMenu = Gtk::manage(new Gtk::MenuItem(_("_Help"), true));
    Gtk::Menu* submenu2 = Gtk::manage(new Gtk::Menu);
    Gtk::MenuItem*aboutMenuItem = Gtk::manage(new Gtk::MenuItem(_("About")));
    submenu2->append(*aboutMenuItem);
    rootHelpMenu->set_submenu(*submenu2);

    return rootHelpMenu;
}

void MenuBar::onQuitMenuItem() {
    Gtk::Main::quit();
}


void MenuBar::onShowSettings(Gtk::Window* parentWindow) {
    SettingsWindow settingsDialog(*parentWindow);
    settingsDialog.run();
}

Gtk::MenuItem* MenuBar::createFilePanelMenu(Glib::ustring panelName) {
    Gtk::MenuItem*rootPanelMenu = Gtk::manage(new Gtk::MenuItem(panelName, true));
    Gtk::Menu* rootPanelSubMenu = Gtk::manage(new Gtk::Menu);
    rootPanelMenu->set_submenu(*rootPanelSubMenu);

    Gtk::MenuItem* sortOrderMenu = Gtk::manage(new Gtk::MenuItem(_("Sort order...")));
    rootPanelSubMenu->append(*sortOrderMenu);

    return rootPanelMenu;
}
