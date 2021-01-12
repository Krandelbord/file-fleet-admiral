
#include <giomm.h>
#include <gtkmm.h>
#include "FileAndDirectoryStaticIconProvider.h"
#include "../config.h"

Glib::RefPtr<Gdk::Pixbuf> FileAndDirectoryStaticIconProvider::getIconForFile(const Glib::ustring &filePath) {
    static Glib::RefPtr<Gtk::IconTheme> iconTheme = Gtk::IconTheme::get_default();
    auto f = Gio::File::create_for_path(filePath);
    const Glib::RefPtr<Gio::FileInfo> &ww = f->query_info();

    Gio::FileType fileType = f->query_file_type();
    if (fileType == Gio::FileType::FILE_TYPE_DIRECTORY) {
        return getIconOrDefault(iconTheme, "folder");
    } else if (fileType == Gio::FileType::FILE_TYPE_SYMBOLIC_LINK) {
        return getIconOrDefault(iconTheme, "emblem-symbolic-link");
    } else if (fileType == Gio::FileType::FILE_TYPE_REGULAR) {
        bool isExecutable = Glib::file_test(filePath, Glib::FileTest::FILE_TEST_IS_EXECUTABLE);
        if (isExecutable) {
            return getIconOrDefault(iconTheme, "application-x-executable");
        }
    }
    return getIconOrDefault(iconTheme, "application-x-generic");
}

Glib::RefPtr<Gdk::Pixbuf>
FileAndDirectoryStaticIconProvider::getIconOrDefault(const Glib::RefPtr<Gtk::IconTheme> &iconTheme,
                                                     const char *iconName) const {
    try {
        return iconTheme->load_icon(iconName, 3);
    } catch (Glib::Error &er) {
        gfm_debug("Error when reading icon %s\n", er.what().c_str());
        return iconTheme->load_icon(iconTheme->get_example_icon_name(), 3);
    }
}
