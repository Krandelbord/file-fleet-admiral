#include "FilesNavigationPanel.h"

FilesNavigationPanel::FilesNavigationPanel(const Settings &settingsToRead) {
    this->set_position(settingsToRead.readPanedPosition());
    Glib::ustring currentDir = Glib::get_current_dir();
 
    SinglePanel* leftPanel = Gtk::manage(new SinglePanel(currentDir));
    this->add1(*leftPanel);

    this->rightPanel = Gtk::manage(new SinglePanel(settingsToRead.getRightDirPath()));
    this->add2(*rightPanel);
}

const Glib::ustring FilesNavigationPanel::getRightPanelDir() const {
    return rightPanel->getCurrentDir();
}

