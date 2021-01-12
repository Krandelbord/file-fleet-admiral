#ifndef FILE_FLEET_ADMIRAL_ICONPROVIDER_H
#define FILE_FLEET_ADMIRAL_ICONPROVIDER_H


class IconProvider {
public:
    IconProvider();

    Glib::RefPtr<Gdk::Pixbuf> getIconOrDefault(const char *iconName) const;

private:
    Glib::RefPtr<Gtk::IconTheme> iconTheme;
};


#endif //FILE_FLEET_ADMIRAL_ICONPROVIDER_H
