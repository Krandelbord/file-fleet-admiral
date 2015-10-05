#ifndef FILES_TREE_VIEW_H
#define FILES_TREE_VIEW_H

#include <gtkmm.h>

class FilesTreeView : public Gtk::TreeView {
    public :
        FilesTreeView(Glib::RefPtr<Gtk::ListStore> filesListStorage);

    private:
    Gtk::CellRendererText * addStyleByTypeTxtColumn(const Gtk::TreeModelColumn<Glib::ustring> &columnToAdd,
                                 const Glib::ustring &columnTitle);

    void addEllipsizedColumn(Gtk::TreeModelColumn<Glib::ustring> column, const Glib::ustring &columnTitle,
                             int sizeInChars);

    //when tree view gets it's focus
    bool onFocusIn(GdkEventFocus* widget);
    //when treeview loses it's focus
    bool onFocusOut(GdkEventFocus* widget);


    std::vector<Gtk::TreeModel::Path> lastlySelectedRow;
};

#endif /** FILES_TREE_VIEW_H **/
