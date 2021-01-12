#ifndef FILE_FLEET_ADMIRAL_FILEANDDIRECTORYSTATICICONPROVIDER_H
#define FILE_FLEET_ADMIRAL_FILEANDDIRECTORYSTATICICONPROVIDER_H


#include "FileTypeIconProvider.h"

class FileAndDirectoryStaticIconProvider : FileTypeIconProvider {
public:
    Glib::RefPtr<Gdk::Pixbuf> getIconForFile(const Glib::ustring &filePath) override;
};


#endif //FILE_FLEET_ADMIRAL_FILEANDDIRECTORYSTATICICONPROVIDER_H
