#include "FilesTreeView.h"
#include "FilesColumns.h"
#include "config.h"

FilesTreeView::FilesTreeView(Glib::RefPtr<Gtk::ListStore> filesListStorage) {
    FilesColumns filesColumns; 
    this->set_model(filesListStorage);

    Gtk::CellRendererText* cell = Gtk::manage(new Gtk::CellRendererText());
    int cols_count = this->append_column(_("Name"), *cell);
    Gtk::TreeViewColumn* pColumn = this->get_column(cols_count - 1);
    if(pColumn) {
        pColumn->add_attribute(cell->property_text(), filesColumns.file_name_column);
        pColumn->add_attribute(cell->property_weight(), filesColumns.font_weight);
    }

    this->append_column(_("Size"), filesColumns.size_column);
}


