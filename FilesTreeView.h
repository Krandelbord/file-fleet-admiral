#ifndef FILES_TREE_VIEW_H
#define FILES_TREE_VIEW_H

#include <gtkmm.h>

class FilesTreeView : public Gtk::TreeView {
    public :
        FilesTreeView(Glib::RefPtr<Gtk::ListStore> filesListStorage);

    private:
    void addStyleByTypeTxtColumn(const Gtk::TreeModelColumn<Glib::ustring> &columnToAdd,
                                 const Glib::ustring &columnTitle);
};

#endif /** FILES_TREE_VIEW_H **/
