#include "FilesTreeView.h"
#include "FilesColumns.h"
#include "config.h"
#include <iostream>

/** Size of column "File name" in chars **/
#define NAME_COLUMN_SIZE_IN_CHARS 70

FilesTreeView::FilesTreeView(Glib::RefPtr<Gtk::ListStore> filesListStorage) {
    FilesColumns filesColumns; 
    this->set_model(filesListStorage);

    addEllipsizedColumn(filesColumns.file_name_column, _("Name"), NAME_COLUMN_SIZE_IN_CHARS);
    addStyleByTypeTxtColumn(filesColumns.size_column, _("Size"));
    //this->get_selection()->set_mode(Gtk::SELECTION_NONE);
    //this->override_cursor(Gdk::RGBA("DarkSlateGray"), Gdk::RGBA("DarkSlateGray"));

    Glib::RefPtr<Gtk::StyleContext> style = Gtk::StyleContext::create();
    style->add_class("GtkWindow {  background-color: red; }");

    Glib::RefPtr<Gtk::CssProvider> css = Gtk::CssProvider::create();
    css->load_from_data("GtkWidget {  background-color: red; }");

    
    Glib::RefPtr<Gtk::StyleContext> treeViewCtx = this->get_style_context();
    treeViewCtx->add_provider( Glib::RefPtr<Gtk::StyleProvider>::cast_static(css), 1);
    std::cout << std::endl << std::endl;
    std::cout << "takie cos: " << this->get_style_context() << "koniec." << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << std::endl << std::endl;
    
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
    if(pColumn) {
        pColumn->add_attribute(cell->property_text(), columnToAdd);
        pColumn->add_attribute(cell->property_weight(), filesColumns.font_weight);
    }
    return cell;
}


void FilesTreeView::addEllipsizedColumn(Gtk::TreeModelColumn<Glib::ustring> column, const Glib::ustring &columnTitle,
                                        int sizeInChars) {
    Gtk::CellRendererText *cellAdded = addStyleByTypeTxtColumn(column, columnTitle);
    cellAdded->property_ellipsize().set_value(Pango::EllipsizeMode::ELLIPSIZE_MIDDLE);
    cellAdded->property_width_chars().set_value(sizeInChars);
}

