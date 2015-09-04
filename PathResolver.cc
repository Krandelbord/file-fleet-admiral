#include "PathResolver.h"

PathResolver::PathResolver(const Glib::ustring& startPath) {
    this->pathAsString = Glib::ustring(startPath);
}

PathResolver PathResolver::changeDirBy(const Glib::ustring& changeDirPath) {
    if (changeDirPath == "..") {
        size_t slashFound = this->pathAsString.find_last_of("/");
        if (slashFound != std::string::npos) {
            this->pathAsString.erase(slashFound);
        }
    } else {
        this->pathAsString.append("/");
        this->pathAsString.append(changeDirPath);
    }
    return PathResolver("");
}

Glib::ustring PathResolver::toString() const {
    return pathAsString;
}
