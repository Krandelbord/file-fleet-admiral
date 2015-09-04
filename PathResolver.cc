#include "PathResolver.h"

PathResolver::PathResolver(const Glib::ustring& startPath) {

}

PathResolver PathResolver::changeDirBy(const Glib::ustring& changeDirPath) {
    return PathResolver("");
}

Glib::ustring PathResolver::toString() const {
    return "cokolwiek";
}
