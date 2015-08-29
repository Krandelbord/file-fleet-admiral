#include <vector>
#include "SinglePanel.h"
#include "FilesColumns.h"
#include "PanelHeader.h"
#include "FileListElement.h"
#include "config.h"

#define PANEL_MARGIN_SIZE 5

SinglePanel::SinglePanel(const Glib::ustring& startDirPath) {
    this->set_margin_start(PANEL_MARGIN_SIZE);
    this->set_margin_end(PANEL_MARGIN_SIZE);
    
    this->dirDisplayed = Glib::ustring(startDirPath);

    Gtk::Box *mainFilesBox = Gtk::manage(new Gtk::VBox()); 

    this->pathHeader = Gtk::manage(new PanelHeader(startDirPath));
    mainFilesBox->pack_start(*this->pathHeader, Gtk::PackOptions::PACK_SHRINK);

    Gtk::ScrolledWindow* scrollWin = Gtk::manage(new Gtk::ScrolledWindow());
    Gtk::TreeView* filesTreeView = createFilesTreeView();
    filesTreeView->signal_row_activated().connect(sigc::mem_fun(*this, &SinglePanel::onRowActivated));
    scrollWin->add(*filesTreeView);
    mainFilesBox->pack_end(*scrollWin, Gtk::PackOptions::PACK_EXPAND_WIDGET);

    this->add(*mainFilesBox);

    //singal launched after GUI is rendered
    Glib::signal_idle().connect(
            sigc::bind_return(sigc::mem_fun(*this, &SinglePanel::startReadDataThread), false));

}

void SinglePanel::startReadDataThread() {
    gfm_debug("reading files data starts here\n");
    this->readDirWorker = new FilesReadWorker(dirDisplayed, FilesSortType::SORT_BY_NAME);
    this->workerThread = Glib::Threads::Thread::create(
            sigc::bind(sigc::mem_fun(readDirWorker, &FilesReadWorker::threadFunction), this));
   // Connect the handler to the dispatcher.
   m_Dispatcher.connect(sigc::mem_fun(*this, &SinglePanel::onNewData));
}

// notify() is called from ExampleWorker::do_work(). It is executed in the worker
// thread. It triggers a call to on_notification_from_worker_thread(), which is
// executed in the GUI thread.
void SinglePanel::notifyNewDataFromThread() {
    m_Dispatcher.emit();
}

Gtk::TreeView* SinglePanel::createFilesTreeView() {
    FilesColumns filesColumns;
    this->refListStore = createFakeData(); 
    
    Gtk::TreeView *treeView = Gtk::manage(new Gtk::TreeView());
    treeView->set_model(refListStore);
    treeView->append_column("Name", filesColumns.file_name_column);
    treeView->append_column("Size", filesColumns.size_column);
    return treeView;
}

void SinglePanel::onNewData() {
    std::vector<FileListElement> dataFromThread = this->readDirWorker->getDataFromThread();
    for (FileListElement oneNewDataElem : dataFromThread) {
        appendOneFile(this->refListStore, oneNewDataElem.getFileSizeInBytes(), oneNewDataElem.getFileName());
    }
}

Glib::RefPtr<Gtk::ListStore> SinglePanel::createFakeData() {
    FilesColumns filesColumns;
    Glib::RefPtr<Gtk::ListStore> refListStore = Gtk::ListStore::create(filesColumns);
    appendOneFile(refListStore, 0, "..");
    return refListStore;
}

void SinglePanel::appendOneFile(Glib::RefPtr<Gtk::ListStore> refListStore, int size, const Glib::ustring& fileName) {
    FilesColumns filesColumns;
    Gtk::TreeModel::Row row = *(refListStore->append());
    row[filesColumns.file_name_column] = Glib::ustring(fileName);
    row[filesColumns.size_column] = size;
}

const Glib::ustring& SinglePanel::getCurrentDir() const {
    return dirDisplayed;
}

void SinglePanel::onRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) {
    Gtk::TreeModel::iterator iter = refListStore->get_iter(path);
    Gtk::TreeRow selectedRow = *iter;

    FilesColumns filesColumns;
    Glib::ustring selectedFileName = selectedRow.get_value(filesColumns.file_name_column);
    gfm_debug("currently selected element is  %s\n", selectedFileName.c_str());
}
