#ifndef FILE_FLEET_ADMIRAL_FILEICONPROVIDER_H
#define FILE_FLEET_ADMIRAL_FILEICONPROVIDER_H


#include <glibmm.h>
#include <gdkmm.h>

class FileIconProvider {
public:
    virtual Glib::RefPtr<Gdk::Pixbuf> getIconForFile(const Glib::ustring &filePath) = 0;
};


#endif //FILE_FLEET_ADMIRAL_FILEICONPROVIDER_H
