#ifndef FILE_FLEET_ADMIRAL_ALWAYSSAMEICONPROVIDER_H
#define FILE_FLEET_ADMIRAL_ALWAYSSAMEICONPROVIDER_H


#include <glibmm.h>
#include <gdkmm.h>
#include "FileIconProvider.h"

class AlwaysSameIconProvider : public FileIconProvider {

public:
    Glib::RefPtr<Gdk::Pixbuf> getIconForFile(const Glib::ustring &filePath) override;
};


#endif //FILE_FLEET_ADMIRAL_ALWAYSSAMEICONPROVIDER_H
