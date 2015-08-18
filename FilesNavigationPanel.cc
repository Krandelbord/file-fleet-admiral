#include "FilesNavigationPanel.h"
#include "SinglePanel.h"

FilesNavigationPanel::FilesNavigationPanel(const Settings &settingsToRead) {
    this->set_position(settingsToRead.readPanedPosition());

    SinglePanel* leftPanel = Gtk::manage(new SinglePanel());
    this->add1(*leftPanel);

    SinglePanel* rightPanel = Gtk::manage(new SinglePanel());
    this->add2(*rightPanel);

}
