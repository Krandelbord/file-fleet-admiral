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

void FilesNavigationPanel::showRenamePopup(Glib::ustring pathToFile, Glib::ustring fileName) {
        Container *theTopLevel = this->get_toplevel();
        auto *window = dynamic_cast<Gtk::Window *>(theTopLevel);
        const Glib::RefPtr<Gio::File> &originalFile = Gio::File::create_for_path(Glib::build_filename(pathToFile, fileName));
        auto *renamePopUp = new RenamePopup(*window, originalFile);
        renamePopUp->show();
}

Glib::ustring FilesNavigationPanel::getRightPanelDir() const {
    return rightPanel->getCurrentDir();
}

