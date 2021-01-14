#ifndef FILES_TREE_VIEW_H
#define FILES_TREE_VIEW_H

/** Transparency of bar in files view when out-of-focus **/
static const double FOCUS_OUT_TRANSPARENCY_BAR = 0.2;

#include <gtkmm.h>

class FilesTreeView : public Gtk::TreeView {
    public :
    FilesTreeView(Glib::RefPtr<Gtk::ListStore> filesListStorage);
    Gtk::TreeModel::Path getHighlitedElement();
    void markRowActive(Gtk::TreeModel::Path path);

private:
    Gtk::CellRendererText * addStyleByTypeTxtColumn(const Gtk::TreeModelColumn<Glib::ustring> &columnToAdd,
                                 const Glib::ustring &columnTitle);

    void addEllipsizedColumn(Gtk::TreeModelColumn<Glib::ustring> column, const Glib::ustring &columnTitle,
                             int sizeInChars);

    void onCursorChanged();

    void changeColor(Gtk::TreeModel::Path pathToChangeColor, const Gdk::RGBA newBgRowColor);

    Gtk::TreeModel::Path lastlySelectedPath;

    bool onFocusOut(const GdkEventFocus* eventFocus);

    bool onFocusIn(const GdkEventFocus* eventFocus);

    const Gdk::RGBA getActiveBarColor();

    const Gdk::RGBA getNotActiveBarColor();

    const Gdk::RGBA getFocusOutBarColor();

    void addIconColumn(Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> columnValue, char *string);
};

#endif /** FILES_TREE_VIEW_H **/
