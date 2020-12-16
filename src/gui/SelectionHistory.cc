#include "SelectionHistory.h"

SelectionHistory::SelectionHistory(const Glib::ustring& currentDir) : lastVisitedDir(currentDir) {
    history[Glib::canonicalize_filename(lastVisitedDir.toString().c_str())] = FileWithInode(Glib::ustring(PARENT_DIR_SYMBOL), -1);
}

Glib::ustring SelectionHistory::getSelectionForDir(const Glib::ustring &dirToSearchSelection) const {
    auto got = history.find(dirToSearchSelection);
    if (got == history.end()) {
        //not history entry found
        return PARENT_DIR_SYMBOL;
    } else {
        return got->second.getFileName();
    }
}

Glib::ustring SelectionHistory::getSelectionForDir(const PathResolver& pathToSearchForSelection) const {
    return getSelectionForDir(pathToSearchForSelection.toString());
}

void SelectionHistory::changeDirBy(const Glib::ustring &dirToChange) {
    if (dirToChange != PARENT_DIR_SYMBOL) {
        history[Glib::canonicalize_filename(lastVisitedDir.toString().c_str())] = FileWithInode(Glib::ustring(dirToChange), -1);
    }
    lastVisitedDir.changeDirBy(dirToChange);
}

void SelectionHistory::changeDirUp() {
}

void SelectionHistory::updateForCurrentDir(Glib::ustring directory, Glib::ustring selectedFileName) {
    history[Glib::canonicalize_filename(directory.c_str())] = FileWithInode(selectedFileName, -1);
}

void SelectionHistory::updateForCurrentDir(Glib::ustring directory, FileWithInode selectedFileName) {
    history[Glib::canonicalize_filename(directory.c_str())] = selectedFileName;
}