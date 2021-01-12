
#include <giomm.h>
#include "FileAndDirectoryStaticIconProvider.h"
#include "IconProvider.h"

Glib::RefPtr<Gdk::Pixbuf> FileAndDirectoryStaticIconProvider::getIconForFile(const Glib::ustring &filePath) {
    IconProvider iconProvider;
    auto file = Gio::File::create_for_path(filePath);
    Gio::FileType fileType = file->query_file_type();
    if (fileType == Gio::FileType::FILE_TYPE_DIRECTORY) {
        return iconProvider.getIconOrDefault("folder");
    } else if (fileType == Gio::FileType::FILE_TYPE_SYMBOLIC_LINK) {
        return iconProvider.getIconOrDefault("emblem-symbolic-link");
    } else if (fileType == Gio::FileType::FILE_TYPE_REGULAR) {
        bool isExecutable = Glib::file_test(filePath, Glib::FileTest::FILE_TEST_IS_EXECUTABLE);
        if (isExecutable) {
            return iconProvider.getIconOrDefault("application-x-executable");
        }
    }
    return iconProvider.getIconOrDefault("application-x-generic");
}