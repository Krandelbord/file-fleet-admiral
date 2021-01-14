#ifndef FILE_FLEET_ADMIRAL_ICONPROVIDER_H
#define FILE_FLEET_ADMIRAL_ICONPROVIDER_H

#include <gtkmm.h>

class IconProvider {
public:
    IconProvider();
    Glib::RefPtr<Gdk::Pixbuf> getIconOrDefault(const char *iconName) const;
    Glib::RefPtr<Gdk::Pixbuf> parentDirIcon();

private:
    Glib::RefPtr<Gtk::IconTheme> iconTheme;
};

#endif //FILE_FLEET_ADMIRAL_ICONPROVIDER_H
