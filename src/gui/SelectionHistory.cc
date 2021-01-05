#include "SelectionHistory.h"

#include <utility>

SelectionHistory::SelectionHistory(const Glib::ustring& currentDir) : lastVisitedDir(currentDir) {
    history[Glib::canonicalize_filename(lastVisitedDir.toString().c_str())] = SelectionHistory::parentDir();
}

FileWithInode SelectionHistory::getSelectionForDir(const Glib::ustring &dirToSearchSelection) const {
    auto got = history.find(dirToSearchSelection);
    if (got == history.end()) {
        //not history entry found
        return SelectionHistory::parentDir();
    } else {
        return got->second;
    }
}

FileWithInode SelectionHistory::getSelectionForDir(const PathResolver& pathToSearchForSelection) const {
    return getSelectionForDir(pathToSearchForSelection.toString());
}

void SelectionHistory::changeDirBy(const Glib::ustring &dirToChange) {
    if (dirToChange != PARENT_DIR_SYMBOL) {
        history[Glib::canonicalize_filename(lastVisitedDir.toString().c_str())] = FileWithInode(Glib::ustring(dirToChange), UNDEFINED_INODE);
    }
    lastVisitedDir.changeDirBy(dirToChange);
}

void SelectionHistory::updateForCurrentDir(const Glib::ustring& directory, FileWithInode selectedFileName) {
    history[Glib::canonicalize_filename(directory.c_str())] = std::move(selectedFileName);
}

FileWithInode SelectionHistory::parentDir() {
    return FileWithInode(Glib::ustring(PARENT_DIR_SYMBOL), UNDEFINED_INODE);
}