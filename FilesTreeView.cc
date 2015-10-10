#include <iostream>
#include "FilesTreeView.h"
#include "FilesColumns.h"
#include "config.h"

/** Size of column "File name" in chars **/
#define NAME_COLUMN_SIZE_IN_CHARS 70

FilesTreeView::FilesTreeView(Glib::RefPtr<Gtk::ListStore> filesListStorage) {
    FilesColumns filesColumns; 
    this->set_model(filesListStorage);

    addEllipsizedColumn(filesColumns.file_name_column, _("Name"), NAME_COLUMN_SIZE_IN_CHARS);
    addStyleByTypeTxtColumn(filesColumns.size_column, _("Size"));
    this->get_selection()->set_mode(Gtk::SELECTION_NONE);
}

/**
 * Adds column styled by font-weight
 */
Gtk::CellRendererText* FilesTreeView::addStyleByTypeTxtColumn(const Gtk::TreeModelColumn<Glib::ustring> &columnToAdd,
                                            const Glib::ustring &columnTitle) {
    FilesColumns filesColumns;
    Gtk::CellRendererText* cell = manage(new Gtk::CellRendererText());
    int cols_count = append_column(columnTitle, *cell);
    Gtk::TreeViewColumn* pColumn = get_column(cols_count - 1);
    if (pColumn) {
        pColumn->add_attribute(cell->property_text(), columnToAdd);
        pColumn->add_attribute(cell->property_weight(), filesColumns.font_weight);
        pColumn->add_attribute(cell->property_background_rgba(), filesColumns.backgroundColor);
    }
    this->signal_cursor_changed().connect(sigc::mem_fun(*this, &FilesTreeView::onCursorChanged));
    return cell;
}


void FilesTreeView::addEllipsizedColumn(Gtk::TreeModelColumn<Glib::ustring> column, const Glib::ustring &columnTitle,
                                        int sizeInChars) {
    Gtk::CellRendererText *cellAdded = addStyleByTypeTxtColumn(column, columnTitle);
    cellAdded->property_ellipsize().set_value(Pango::EllipsizeMode::ELLIPSIZE_MIDDLE);
    cellAdded->property_width_chars().set_value(sizeInChars);
}



Gtk::TreeModel::Path FilesTreeView::getHighlitedElement() {
    Gtk::TreeModel::Path path;
    Gtk::TreeViewColumn *focusColumn;
    this->get_cursor(path, *&focusColumn);
    return path;
}

void FilesTreeView::onCursorChanged() {
    Gtk::TreeModel::Path currentlySelected = getHighlitedElement();

    if (lastlySelectedPath && lastlySelectedPath == currentlySelected) {
        //same thing selected twice
        return;
    } else {
        changeColor(currentlySelected, Gdk::RGBA("lightblue"));
        changeColor(lastlySelectedPath, Gdk::RGBA("white"));

        lastlySelectedPath = Gtk::TreeModel::Path(currentlySelected);
    }
}

void FilesTreeView::changeColor(Gtk::TreeModel::Path pathToChangeColor, Gdk::RGBA newBgRowColor) {
    if (pathToChangeColor) {
        Gtk::TreeModel::iterator iter = this->get_model()->get_iter(pathToChangeColor);
        FilesColumns filesColumns;
        (*iter).set_value(filesColumns.backgroundColor, newBgRowColor);
    }
}
