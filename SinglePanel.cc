#include "SinglePanel.h"
#include "FilesColumns.h"
#include "PanelHeader.h"
#include "config.h"

#define PANEL_MARGIN_SIZE 5

SinglePanel::SinglePanel(const Glib::ustring& startDirPath) {
    this->set_margin_start(PANEL_MARGIN_SIZE);
    this->set_margin_end(PANEL_MARGIN_SIZE);
    
    Gtk::Box *mainFilesBox = Gtk::manage(new Gtk::VBox());
    
    Gtk::TreeView *filesTreeView = createFilesTreeView();
    this->pathHeader = Gtk::manage(new PanelHeader(startDirPath));
    mainFilesBox->pack_start(*this->pathHeader, Gtk::PackOptions::PACK_SHRINK);
    mainFilesBox->pack_end(*filesTreeView, Gtk::PackOptions::PACK_EXPAND_WIDGET);

    this->add(*mainFilesBox);

    Glib::signal_idle().connect(
            sigc::bind_return(sigc::mem_fun(*this, &SinglePanel::startReadDataThread), false));

}

void SinglePanel::startReadDataThread() {
    gfm_debug("reading files data should start here\n");
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
