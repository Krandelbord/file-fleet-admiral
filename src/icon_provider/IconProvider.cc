
#include <gtkmm.h>
#include "IconProvider.h"
#include "../config.h"
#include "../settings/Settings.h"

IconProvider::IconProvider() {
    this->iconTheme = Gtk::IconTheme::get_default();
}

Glib::RefPtr<Gdk::Pixbuf> IconProvider::getIconOrDefault(const char *iconName) const {
    try {
        return iconTheme->load_icon(iconName, Settings::DEFAULT_ICON_SIZE);
    } catch (Glib::Error &error) {
        gfm_debug("Error when reading icon %s\n", error.what().c_str());
        return iconTheme->load_icon(iconTheme->get_example_icon_name(), Settings::DEFAULT_ICON_SIZE);
    }
}

Glib::RefPtr<Gdk::Pixbuf> IconProvider::parentDirIcon() {
    return getIconOrDefault("folder");
}

