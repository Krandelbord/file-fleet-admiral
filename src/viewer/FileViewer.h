#ifndef FILE_FLEET_ADMIRAL_FILEVIEWER_H
#define FILE_FLEET_ADMIRAL_FILEVIEWER_H


#include <glibmm/ustring.h>

class FileViewer {

public:
    explicit FileViewer(const Glib::ustring &directory, const Glib::ustring &pathToView);
    void show();
private:
    Glib::ustring fileName;
    Glib::ustring directory;
};


#endif //FILE_FLEET_ADMIRAL_FILEVIEWER_H
