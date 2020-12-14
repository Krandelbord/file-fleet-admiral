#ifndef FILES_NAVIGATION_PANEL_H
#define FILES_NAVIGATION_PANEL_H

#include <gtkmm.h>
#include "../../settings/Settings.h"
#include "SinglePanel.h"
#include "../../operations/NotifiableByContentChange.h"

class FilesNavigationPanel : public Gtk::HPaned, NotifiableByContentChange {
    public:
        FilesNavigationPanel(const Settings &settings);
        Glib::ustring getRightPanelDir() const;

    private:
        SinglePanel* leftPanel;
        SinglePanel* rightPanel;
        void showRenamePopup(Glib::ustring path, Glib::ustring fileName);
        void showMovePopup(const Glib::RefPtr<Gio::File>& fileToMove,  SinglePanel* destination);
        void refreshPanelWithDir(const Glib::RefPtr<Gio::File>& changedDir);
};

#endif
