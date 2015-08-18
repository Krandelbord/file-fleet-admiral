#ifndef FILES_NAVIGATION_PANEL_H
#define FILES_NAVIGATION_PANEL_H

#include <gtkmm.h>
#include "Settings.h"

class FilesNavigationPanel : public Gtk::HPaned {
    public:
        FilesNavigationPanel(const Settings &settings);
};

#endif
