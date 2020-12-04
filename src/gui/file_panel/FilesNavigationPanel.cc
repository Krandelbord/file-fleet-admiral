#include "FilesNavigationPanel.h"
#include "../RenamePopup.h"

FilesNavigationPanel::FilesNavigationPanel(const Settings &settingsToRead) {
    this->set_position(settingsToRead.readPanedPosition());
    Glib::ustring currentDir = Glib::get_current_dir();
 
    SinglePanel* leftPanel = Gtk::manage(new SinglePanel(currentDir));
    this->add1(*leftPanel);
    leftPanel->signalShowRename().connect(sigc::mem_fun(*this, &FilesNavigationPanel::showRenamePopup));

    this->rightPanel = Gtk::manage(new SinglePanel(settingsToRead.getRightDirPath()));
    rightPanel->signalShowRename().connect(sigc::mem_fun(*this, &FilesNavigationPanel::showRenamePopup));
    this->add2(*rightPanel);
}

void FilesNavigationPanel::showRenamePopup(Glib::ustring path) {
        Container *theTopLevel = this->get_toplevel();
        auto *window = dynamic_cast<Gtk::Window *>(theTopLevel);
        RenamePopup *pPopup = Gtk::manage(new RenamePopup(*window, path));
        pPopup->show();
}

Glib::ustring FilesNavigationPanel::getRightPanelDir() const {
    return rightPanel->getCurrentDir();
}

