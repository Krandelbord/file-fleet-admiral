#include "SinglePanel.h"
#include "FilesColumns.h"

SinglePanel::SinglePanel(const Glib::ustring& startDirPath) {
    Gtk::TreeView *filesTreeView = createFilesTreeView();
    this->add(*filesTreeView);

    Gtk::Label *bottomStatusBar = new Gtk::Label(startDirPath);
    this->pack_end(*bottomStatusBar, Gtk::PackOptions::PACK_SHRINK);
}

Gtk::TreeView* SinglePanel::createFilesTreeView() {
    FilesColumns *filesColumns = new FilesColumns(); //TODO: nie moze tak byc
    Glib::RefPtr<Gtk::ListStore> refListStore = Gtk::ListStore::create(*filesColumns);
    Gtk::TreeView *treeView = Gtk::manage(new Gtk::TreeView());
    treeView->set_model(refListStore);

    Gtk::TreeModel::Row row = *(refListStore->append());
    row[filesColumns->file_name_column] = Glib::ustring("chyba nie ");
    //treeView->append_column("ID", filesColumns->file_name_column);
    treeView->append_column("ID", filesColumns->size_column);
    return treeView;
}
