#include <iostream>
#include "FilesTreeView.h"
#include "FilesColumns.h"
#include "../../config.h"

/** Size of column "File name" in chars **/
#define NAME_COLUMN_SIZE_IN_CHARS 70

FilesTreeView::FilesTreeView(Glib::RefPtr<Gtk::ListStore> filesListStorage) {
    FilesColumns filesColumns;
    this->set_model(filesListStorage);
    this->append_column("icon", filesColumns.icon);

    addEllipsizedColumn(filesColumns.file_name_column, _("Name"), NAME_COLUMN_SIZE_IN_CHARS);
    addStyleByTypeTxtColumn(filesColumns.size_column, _("Size"));

    this->set_enable_search(false);
    this->get_selection()->set_mode(Gtk::SELECTION_NONE);

    this->signal_focus_out_event().connect(sigc::mem_fun(*this, &FilesTreeView::onFocusOut));
    this->signal_focus_in_event().connect(sigc::mem_fun(*this, &FilesTreeView::onFocusIn));
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

    if (!lastlySelectedPath.empty() & !currentlySelected.empty() && (lastlySelectedPath == currentlySelected)) {
        //same thing selected twice
        return;
    } else {
        if (this->has_focus()) {
            changeColor(currentlySelected, getActiveBarColor());
        }
        changeColor(lastlySelectedPath, getNotActiveBarColor());

        lastlySelectedPath = Gtk::TreeModel::Path(currentlySelected);
    }
}

void FilesTreeView::changeColor(Gtk::TreeModel::Path pathToChangeColor, const Gdk::RGBA newBgRowColor) {
    if (pathToChangeColor) {
        Gtk::TreeModel::iterator iter = this->get_model()->get_iter(pathToChangeColor);
        FilesColumns filesColumns;

        if (iter) {
            (*iter).set_value(filesColumns.backgroundColor, newBgRowColor);
        }
    }
}

bool FilesTreeView::onFocusOut(const GdkEventFocus* eventFocus) {
    const Gtk::TreeModel::Path highlitedElement = getHighlitedElement();
    changeColor(highlitedElement, getFocusOutBarColor());
    return false;
}

bool FilesTreeView::onFocusIn(const GdkEventFocus* eventFocus) {
    const Gtk::TreeModel::Path highlitedElement = getHighlitedElement();
    changeColor(highlitedElement, getActiveBarColor());
    return false;
}

const Gdk::RGBA FilesTreeView::getActiveBarColor() {
    const Glib::RefPtr<Gtk::StyleContext> &style = this->get_style_context();
    return style->get_background_color(Gtk::StateFlags::STATE_FLAG_SELECTED);
}

const Gdk::RGBA FilesTreeView::getNotActiveBarColor() {
    const Glib::RefPtr<Gtk::StyleContext> &style = this->get_style_context();
    return style->get_background_color(Gtk::StateFlags::STATE_FLAG_NORMAL);
}

const Gdk::RGBA FilesTreeView::getFocusOutBarColor() {
    Gdk::RGBA focusOutColor = Gdk::RGBA(getActiveBarColor());
    focusOutColor.set_alpha(FOCUS_OUT_TRANSPARENCY_BAR);
    return focusOutColor;
}

void FilesTreeView::markRowActive(Gtk::TreeModel::Path path) {
    changeColor(path, getActiveBarColor());
}
