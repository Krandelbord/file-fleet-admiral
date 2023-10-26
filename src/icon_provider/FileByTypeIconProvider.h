#ifndef FILE_FLEET_ADMIRAL_FILEBYTYPEICONPROVIDER_H
#define FILE_FLEET_ADMIRAL_FILEBYTYPEICONPROVIDER_H


#include "FileIconProvider.h"

class FileByTypeIconProvider : public FileIconProvider {
public:
    Glib::RefPtr<Gdk::Pixbuf> getIconForFile(const Glib::ustring &filePath) override;
};


#endif //FILE_FLEET_ADMIRAL_FILEBYTYPEICONPROVIDER_H
