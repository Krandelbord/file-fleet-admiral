#include "AlwaysSameIconProvider.h"

Glib::RefPtr<Gdk::Pixbuf> AlwaysSameIconProvider::getIconForFile(const Glib::ustring &filePath) {
    return Gdk::Pixbuf::create_from_file("/usr/share/icons/Moka/22x22/places/debian.png");
}
