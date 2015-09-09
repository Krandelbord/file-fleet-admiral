#include "SelectionHistory.h"
#include "config.h"

SelectionHistory::SelectionHistory(const Glib::ustring& currentDir) : lastVisitedDir(currentDir) {
    history[currentDir] = PARENT_DIR_SYMBOL;
}

Glib::ustring SelectionHistory::getSelectionForDir(const Glib::ustring &dirToSearchSelection) const {
    std::unordered_map<std::string, std::string>::const_iterator got = history.find(dirToSearchSelection);
    if (got == history.end()) {
        //not history entry found
        return PARENT_DIR_SYMBOL;
    } else {
        return got->second;
    }
}

Glib::ustring SelectionHistory::getSelectionForDir(const PathResolver& pathToSearchForSelection) const {
    return getSelectionForDir(pathToSearchForSelection.toString());
}

void SelectionHistory::changeDirBy(const Glib::ustring &dirToChange) {
    if (dirToChange != PARENT_DIR_SYMBOL) {
        history[lastVisitedDir.toString()] = Glib::ustring(dirToChange);
    }
    lastVisitedDir.changeDirBy(dirToChange);
}

void SelectionHistory::changeDirUp() {
}


