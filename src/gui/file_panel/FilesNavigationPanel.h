#ifndef FILES_NAVIGATION_PANEL_H
#define FILES_NAVIGATION_PANEL_H

#include <gtkmm.h>
#include "../../settings/Settings.h"
#include "SinglePanel.h"

class FilesNavigationPanel : public Gtk::HPaned {
    public:
        FilesNavigationPanel(const Settings &settings);
        Glib::ustring getRightPanelDir() const;

    private:
        SinglePanel* rightPanel;
        void showRenamePopup(Glib::ustring path, Glib::ustring fileName);
};

#endif
