#ifndef FILE_FLEET_ADMIRAL_FILETYPEICONPROVIDER_H
#define FILE_FLEET_ADMIRAL_FILETYPEICONPROVIDER_H


#include <glibmm.h>
#include <gdkmm.h>

class FileTypeIconProvider {
public:
    virtual Glib::RefPtr<Gdk::Pixbuf> getIconForFile(const Glib::ustring &filePath) = 0;
};


#endif //FILE_FLEET_ADMIRAL_FILETYPEICONPROVIDER_H
