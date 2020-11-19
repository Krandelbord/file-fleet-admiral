//
// Created by emil on 19.11.2020.
//

#include <giomm.h>
#include <iostream>
#include "FileViewer.h"
#include "../config.h"

void FileViewer::show() {
    gfm_debug("This should open file view for %s\n", this->fileName.c_str());
    std::vector<Glib::ustring> pathElements = {directory, fileName};
    Glib::ustring absolutePath = Glib::build_path(G_DIR_SEPARATOR_S, pathElements);
    std::vector<std::string> args = {"see", absolutePath};
    Glib::spawn_async("", args, Glib::SPAWN_SEARCH_PATH);
}

FileViewer::FileViewer(const Glib::ustring &directory, const Glib::ustring &pathToView) {
    this->fileName = Glib::ustring(pathToView);
    this->directory = Glib::ustring(directory);
}
