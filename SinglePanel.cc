#include "SinglePanel.h"
#include "FilesColumns.h"

SinglePanel::SinglePanel(const Glib::ustring& startDirPath) {
    Gtk::TreeView *filesTreeView = createFilesTreeView();
    this->add(*filesTreeView);

    Gtk::Label *bottomStatusBar = new Gtk::Label(startDirPath);
    this->pack_end(*bottomStatusBar, Gtk::PackOptions::PACK_SHRINK);
}

Gtk::TreeView* SinglePanel::createFilesTreeView() {
    FilesColumns filesColumns;
    Glib::RefPtr<Gtk::ListStore> refListStore = createFakeData(); 
    
    Gtk::TreeView *treeView = Gtk::manage(new Gtk::TreeView());
    treeView->set_model(refListStore);
    treeView->append_column("Name", filesColumns.file_name_column);
    treeView->append_column("Size", filesColumns.size_column);



    return treeView;
}

Glib::RefPtr<Gtk::ListStore> SinglePanel::createFakeData() {
    FilesColumns filesColumns;
    Glib::RefPtr<Gtk::ListStore> refListStore = Gtk::ListStore::create(filesColumns);
    appendOneFile(refListStore, 0, "...");
    appendOneFile(refListStore, 3443, "some file name");
    return refListStore;
}

void SinglePanel::appendOneFile(Glib::RefPtr<Gtk::ListStore> refListStore, int size, const Glib::ustring& fileName) {
    FilesColumns filesColumns;
    Gtk::TreeModel::Row row = *(refListStore->append());
    row[filesColumns.file_name_column] = Glib::ustring(fileName);
    row[filesColumns.size_column] = size;
}
