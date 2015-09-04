#include "PathResolver.h"
#include <glib/gfileutils.h>

PathResolver::PathResolver(const Glib::ustring& startPath) {
    this->pathAsString = Glib::ustring(startPath);
}

void PathResolver::changeDirBy(const Glib::ustring& changeDirPath) {
    if (changeDirPath == PARENT_DIR_SYMBOL && this->pathAsString == G_DIR_SEPARATOR_S) {
        //stay in root dir
        return;
    }
    if (changeDirPath == PARENT_DIR_SYMBOL) {
        changeDirUp();
    } else {
        this->pathAsString.append(G_DIR_SEPARATOR_S);
        this->pathAsString.append(changeDirPath);
    }
}

void PathResolver::changeDirUp() {
    size_t slashFound = this->pathAsString.find_last_of(G_DIR_SEPARATOR_S);
    if (slashFound != std::string::npos) {
        this->pathAsString.erase(slashFound);
        if (this->pathAsString.empty()) {
            this->pathAsString = G_DIR_SEPARATOR_S;
        }
    }
}

Glib::ustring PathResolver::toString() const {
    return pathAsString;
}
