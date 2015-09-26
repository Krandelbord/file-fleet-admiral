#ifndef SELECTION_HISTORY_H
#define SELECTION_HISTORY_H

#include <unordered_map>
#include <glibmm.h>
#include "PathResolver.h"

class SelectionHistory {
    public:
        SelectionHistory(const Glib::ustring& currentDir);
        Glib::ustring getSelectionForDir(const Glib::ustring &dirToSearchSelection) const;
        Glib::ustring getSelectionForDir(const PathResolver& pathToSearchForSelection) const;

        void changeDirBy(const Glib::ustring &dirToChange);
        void changeDirUp();

    private:
        std::unordered_map<std::string, std::string> history;
        PathResolver lastVisitedDir;
};
#endif /** SELECTION_HISTORY_H */
