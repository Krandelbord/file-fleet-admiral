#ifndef FILES_COLUMNS_H
#define FILES_COLUMNS_H

#include <gtkmm.h>

class FilesColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        FilesColumns();
        Gtk::TreeModelColumn<int> size_column;
        Gtk::TreeModelColumn<Glib::ustring> file_name_column;
};

#endif /** FILES_COLUMNS_H **/
