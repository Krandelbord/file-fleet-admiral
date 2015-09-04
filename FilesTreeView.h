#ifndef FILES_TREE_VIEW_H
#define FILES_TREE_VIEW_H

#include <gtkmm.h>
class FilesTreeView : public Gtk::TreeView {
    public :
        FilesTreeView(Glib::RefPtr<Gtk::ListStore> filesListStorage);
};

#endif /** FILES_TREE_VIEW_H **/
