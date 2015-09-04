#include <vector>
#include <stdexcept>
#include "SinglePanel.h"
#include "FilesColumns.h"
#include "PanelHeader.h"
#include "FileListElement.h"
#include "FilesTreeView.h"
#include "PathResolver.h"
#include "config.h"

#define PANEL_MARGIN_SIZE 5
#define NOT_BOLDED_TXT 400
#define BOLDED_TXT 2*NOT_BOLDED_TXT

SinglePanel::SinglePanel(const Glib::ustring& startDirPath) {
    this->set_margin_start(PANEL_MARGIN_SIZE);
    this->set_margin_end(PANEL_MARGIN_SIZE);
    
    Gtk::Box *mainFilesBox = Gtk::manage(new Gtk::VBox()); 

    this->pathHeader = Gtk::manage(new PanelHeader(startDirPath));
    this->setCurrentDir(startDirPath);

    mainFilesBox->pack_start(*this->pathHeader, Gtk::PackOptions::PACK_SHRINK);

    Gtk::ScrolledWindow* scrollWin = Gtk::manage(new Gtk::ScrolledWindow());
    createEmptyData();
    Gtk::TreeView* filesTreeView = Gtk::manage(new FilesTreeView(refListStore));
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

void SinglePanel::onNewData() {
    std::vector<FileListElement> dataFromThread = this->readDirWorker->getDataFromThread();
    for (FileListElement& oneNewDataElem : dataFromThread) {
        appendOneFile(this->refListStore, oneNewDataElem);
    }
}

void SinglePanel::createEmptyData() {
    FilesColumns filesColumns;
    this->refListStore = Gtk::ListStore::create(filesColumns);
    FileListElement parent = FileListElement::createParentDir();
    appendOneFile(refListStore, parent);
}

void SinglePanel::appendOneFile(Glib::RefPtr<Gtk::ListStore> refListStore, FileListElement& oneNewDataElem) {
    FilesColumns filesColumns;
    Gtk::TreeModel::Row row = *(refListStore->append());
    row[filesColumns.file_name_column] = Glib::ustring(oneNewDataElem.getFileName());
    row[filesColumns.size_column] = oneNewDataElem.getFileSizeInBytes();
    row[filesColumns.font_weight] = oneNewDataElem.getFileType() == FileType::DIRECTORY ? BOLDED_TXT : NOT_BOLDED_TXT;
}

const Glib::ustring& SinglePanel::getCurrentDir() const {
    return dirDisplayed;
}

void SinglePanel::onRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) {
    if (refListStore) {
    Gtk::TreeModel::iterator iter = refListStore->get_iter(path);
    Gtk::TreeRow selectedRow = *iter;

    FilesColumns filesColumns;
    Glib::ustring selectedFileName = selectedRow.get_value(filesColumns.file_name_column);
    PathResolver pathResolver(this->dirDisplayed);
    pathResolver.changeDirBy(selectedFileName);

    gfm_debug("currently selected element is  %s\n", selectedFileName.c_str());
    gfm_debug("new file name is %s\n", pathResolver.toString().c_str());
    this->setCurrentDir(pathResolver.toString());

    //start reading
    refListStore->clear();
    FileListElement parent = FileListElement::createParentDir();
    appendOneFile(refListStore, parent);
    delete this->readDirWorker;
    gfm_debug("before workerThread->join()\n");
    workerThread->join(); //closes thread but might block here for some reasone
    gfm_debug("after workerThread->join()\n");
    this->readDirWorker = new FilesReadWorker(pathResolver.toString(), FilesSortType::SORT_BY_NAME);
    this->workerThread = Glib::Threads::Thread::create(
            sigc::bind(sigc::mem_fun(readDirWorker, &FilesReadWorker::threadFunction), this));

    } else {
        throw std::runtime_error("list store is completly empty");
    }
}

void SinglePanel::setCurrentDir(const Glib::ustring& newCurrentDir) {
    this->dirDisplayed = Glib::ustring(newCurrentDir);
    this->pathHeader->setCurrentDir(newCurrentDir);
}
