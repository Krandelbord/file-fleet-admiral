#ifndef SINGLE_PANEL_H
#define SINGLE_PANEL_H

#include <gtkmm.h>
/**
 * Represents single panel for files
**/
class SinglePanel : public Gtk::VBox {
    public:
        SinglePanel(const Glib::ustring& startDirPath);
    private:
        Gtk::TreeView* createFilesTreeView();
        Glib::RefPtr<Gtk::ListStore> createFakeData();
        void appendOneFile(Glib::RefPtr<Gtk::ListStore> refListStore, int size, const Glib::ustring& fileName);
};

#endif /** SINGLE_PANEL_H */
