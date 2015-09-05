#include "FilesTreeView.h"
#include "FilesColumns.h"
#include "config.h"

FilesTreeView::FilesTreeView(Glib::RefPtr<Gtk::ListStore> filesListStorage) {
    FilesColumns filesColumns; 
    this->set_model(filesListStorage);

    addStyleByTypeTxtColumn(filesColumns.file_name_column, _("Name"));
    addStyleByTypeTxtColumn(filesColumns.size_column, _("Size"));
}

/**
 * Adds column styled by font-weight
 */
void FilesTreeView::addStyleByTypeTxtColumn(const Gtk::TreeModelColumn<Glib::ustring> &columnToAdd,
                                            const Glib::ustring &columnTitle) {
    FilesColumns filesColumns;
    Gtk::CellRendererText* cell = manage(new Gtk::CellRendererText());
    int cols_count = append_column(columnTitle, *cell);
    Gtk::TreeViewColumn* pColumn = get_column(cols_count - 1);
    if(pColumn) {
        pColumn->add_attribute(cell->property_text(), columnToAdd);
        pColumn->add_attribute(cell->property_weight(), filesColumns.font_weight);
    }
}


