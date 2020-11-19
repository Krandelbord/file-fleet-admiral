//
// Created by emil on 19.11.2020.
//

#include "FileViewer.h"
#include "../config.h"

void FileViewer::show() {
    gfm_debug("This should open file view for %s\n", this->pathToView.c_str());
}

FileViewer::FileViewer(const Glib::ustring &pathToView) {
    this->pathToView = Glib::ustring(pathToView);
}
