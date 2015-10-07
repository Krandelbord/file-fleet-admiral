#ifndef FILES_NAVIGATION_PANEL_H
#define FILES_NAVIGATION_PANEL_H

#include <gtkmm.h>
#include "Settings.h"
#include "SinglePanel.h"

class FilesNavigationPanel : public Gtk::HPaned {
    public:
        FilesNavigationPanel(const Settings &settings);
        const Glib::ustring getRightPanelDir() const;

    private:
        SinglePanel* rightPanel;
};

#endif
