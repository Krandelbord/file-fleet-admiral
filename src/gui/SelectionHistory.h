#ifndef SELECTION_HISTORY_H
#define SELECTION_HISTORY_H

#include <unordered_map>
#include <glibmm.h>
#include "PathResolver.h"
#include "FileWithInode.h"


class SelectionHistory {
    public:
        SelectionHistory(const Glib::ustring& currentDir);
        FileWithInode getSelectionForDir(const Glib::ustring &dirToSearchSelection) const;
        FileWithInode getSelectionForDir(const PathResolver& pathToSearchForSelection) const;

        static FileWithInode parentDir();
        void changeDirBy(const Glib::ustring &dirToChange);
        void changeDirUp();
        void updateForCurrentDir(const Glib::ustring& ustring, Glib::ustring selectedFileName);
        void updateForCurrentDir(const Glib::ustring& directory, FileWithInode selectedFileName);

    private:
        std::unordered_map<std::string, FileWithInode> history;
        PathResolver lastVisitedDir;
};

#endif /** SELECTION_HISTORY_H */
