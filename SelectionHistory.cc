#include "SelectionHistory.h"
#include "config.h"

SelectionHistory::SelectionHistory(const Glib::ustring& currentDir) {
    history[currentDir] = "..";
    lastVisitedDir = currentDir;
}

Glib::ustring SelectionHistory::getSelectionForDir(const Glib::ustring &dirToSearchSelection) const {
    gfm_debug("Searching for history of %s\n", dirToSearchSelection.c_str());
    std::unordered_map<std::string, std::string>::const_iterator got = history.find(dirToSearchSelection);
    if (got == history.end()) {
        gfm_debug("not found niestety \n");
        //not found -- default is dir UP
        return "..";
    } else {
        return got->second;
    }
}

Glib::ustring SelectionHistory::getSelectionForDir(const PathResolver& pathToSearchForSelection) const {
    return getSelectionForDir(pathToSearchForSelection.toString());
}

void SelectionHistory::changeDirBy(const Glib::ustring &dirToChange) {
    gfm_debug("dodanie do klucza %s wartosci %s\n", lastVisitedDir.c_str(), dirToChange.c_str());
    history[lastVisitedDir] = Glib::ustring(dirToChange);
    lastVisitedDir = lastVisitedDir+"/"+dirToChange;
}

void SelectionHistory::changeDirUp() {
}


