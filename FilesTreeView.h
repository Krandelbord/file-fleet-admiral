#ifndef FILES_TREE_VIEW_H
#define FILES_TREE_VIEW_H

#include <gtkmm.h>

class FilesTreeView : public Gtk::TreeView {
    public :
    FilesTreeView(Glib::RefPtr<Gtk::ListStore> filesListStorage);
    Gtk::TreeModel::Path getHighlitedElement();

private:
    Gtk::CellRendererText * addStyleByTypeTxtColumn(const Gtk::TreeModelColumn<Glib::ustring> &columnToAdd,
                                 const Glib::ustring &columnTitle);

    void addEllipsizedColumn(Gtk::TreeModelColumn<Glib::ustring> column, const Glib::ustring &columnTitle,
                             int sizeInChars);

    void onCursorChanged();

    void changeColor(Gtk::TreeModel::Path pathToChangeColor, Gdk::RGBA newBgRowColor);

    Gtk::TreeModel::Path lastlySelectedPath;
};

#endif /** FILES_TREE_VIEW_H **/
