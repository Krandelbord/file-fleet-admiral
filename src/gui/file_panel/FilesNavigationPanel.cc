#include "FilesNavigationPanel.h"
#include "../RenamePopup.h"
#include "../../config.h"

FilesNavigationPanel::FilesNavigationPanel(const Settings &settingsToRead) {
    this->set_position(settingsToRead.readPanedPosition());
    Glib::ustring currentDir = Glib::get_current_dir();
 
    leftPanel = Gtk::manage(new SinglePanel(currentDir));
    this->add1(*leftPanel);
    leftPanel->signalShowRename().connect(sigc::mem_fun(*this, &FilesNavigationPanel::showRenamePopup));

    this->rightPanel = Gtk::manage(new SinglePanel(settingsToRead.getRightDirPath()));
    rightPanel->signalShowRename().connect(sigc::mem_fun(*this, &FilesNavigationPanel::showRenamePopup));
    this->add2(*rightPanel);

    this->refreshDirViewSignal.connect(sigc::mem_fun(*this, &FilesNavigationPanel::refreshPanelWithDir));
}

void FilesNavigationPanel::showRenamePopup(Glib::ustring pathToFile, Glib::ustring fileName) {
        Container *theTopLevel = this->get_toplevel();
        auto *window = dynamic_cast<Gtk::Window *>(theTopLevel);
        const Glib::RefPtr<Gio::File> &originalFile = Gio::File::create_for_path(Glib::build_filename(pathToFile, fileName));
        auto *renamePopUp = new RenamePopup(*window, this, originalFile);
        renamePopUp->show();
}

Glib::ustring FilesNavigationPanel::getRightPanelDir() const {
    return rightPanel->getCurrentDir();
}

void FilesNavigationPanel::refreshPanelWithDir(const Glib::RefPtr<Gio::File>& changedDir) {
    gfm_debug("Should refresh dir %s\n", changedDir->get_path().c_str());
    if (leftPanel->getCurrentDir() == changedDir->get_path()) {
        leftPanel->refreshCurrentDir();
    }
}

