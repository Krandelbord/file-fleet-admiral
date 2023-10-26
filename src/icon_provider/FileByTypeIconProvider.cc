#include <gtkmm.h>
#include "FileByTypeIconProvider.h"
#include "../settings/Settings.h"

/**
 * Provides separate icon for each file type.
 * Same dir to read using this takes 529 778us, in FileAndDirectoryStaticIconProvider takes 27 695us (19 times faster)
 * @param filePath
 * @return
 */
Glib::RefPtr<Gdk::Pixbuf> FileByTypeIconProvider::getIconForFile(const Glib::ustring &filePath) {
    const Glib::RefPtr<Gtk::IconTheme> &theme = Gtk::IconTheme::get_default();
    auto file = Gio::File::create_for_path(filePath);
    const Glib::RefPtr<Gio::FileInfo> &fileInfo = file->query_info();
    const Glib::RefPtr<Gio::Icon> &theIcon = fileInfo->get_icon();
    const Gtk::IconInfo &foundIcon = theme->lookup_icon(theIcon, Settings::DEFAULT_ICON_SIZE);
    return foundIcon.load_icon();
}
