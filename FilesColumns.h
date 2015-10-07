#ifndef FILES_COLUMNS_H
#define FILES_COLUMNS_H

#include <gtkmm.h>

class FilesColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        FilesColumns();

        /** When adding new columns we need to add them to constructor as well **/
        Gtk::TreeModelColumn<Glib::ustring> size_column;
        Gtk::TreeModelColumn<Glib::ustring> file_name_column;
        Gtk::TreeModelColumn<int> font_weight;
};

#endif /** FILES_COLUMNS_H **/
