#include <vector>
#include <memory>
#include <iostream>
#include "SinglePanel.h"
#include "FilesColumns.h"
#include "config.h"
#include "Preconditions.h"

#define PANEL_MARGIN_SIZE 5
#define NOT_BOLDED_TXT 400
#define BOLDED_TXT 2*NOT_BOLDED_TXT

SinglePanel::SinglePanel(const Glib::ustring& startDirPath) :
        currentDir(startDirPath), selectionHistory(startDirPath) {

    this->set_margin_start(PANEL_MARGIN_SIZE);
    this->set_margin_end(PANEL_MARGIN_SIZE);
    
    Gtk::Box *mainFilesBox = Gtk::manage(new Gtk::VBox()); 

    this->pathHeader = Gtk::manage(new PanelHeader(startDirPath));
    this->updateCurrentDirHeader();
    mainFilesBox->pack_start(*this->pathHeader, Gtk::PackOptions::PACK_SHRINK);
    mainFilesBox->pack_end(filePanelFooter, Gtk::PackOptions::PACK_SHRINK);

    Gtk::ScrolledWindow* scrollWin = Gtk::manage(new Gtk::ScrolledWindow());
    createEmptyData();
    this->filesTreeView = Gtk::manage(new FilesTreeView(refListStore));
    filesTreeView->signal_row_activated().connect(sigc::mem_fun(*this, &SinglePanel::onRowActivated));
    filesTreeView->signal_cursor_changed().connect(sigc::mem_fun(*this, &SinglePanel::onCursorChanged));
    scrollWin->add(*filesTreeView);
    mainFilesBox->pack_end(*scrollWin, Gtk::PackOptions::PACK_EXPAND_WIDGET);

    this->add(*mainFilesBox);
    //singal launched after GUI is rendered
    Glib::signal_idle().connect(
            sigc::bind_return(sigc::mem_fun(*this, &SinglePanel::startReadDataThread), false));

}

void SinglePanel::startReadDataThread() {
    gfm_debug("reading files data starts here\n");
    
    std::shared_ptr<ThreadMessage> threadMsng = std::make_shared<ThreadMessage>(currentDir);
    guiDataReader.commandReadThis(threadMsng);
    // Connect the handler to the dispatcher.
    threadMsng->connectWorkFinishedSignal(sigc::mem_fun(*this, &SinglePanel::onNewData));
}

void SinglePanel::onNewData() {
    std::vector<FileListElement> dataFromThread = guiDataReader.getCalculatedData();
    for (FileListElement& oneNewDataElem : dataFromThread) {
        appendOneFile(this->refListStore, oneNewDataElem);
    }
    this->stopProgressIndicator();
    this->putFocusOnTopOfTreeview();
}

void SinglePanel::createEmptyData() {
    if (refListStore) {
        refListStore->clear();
    } else {
        FilesColumns filesColumns;
        this->refListStore = Gtk::ListStore::create(filesColumns);
    }
    FileListElement parent = FileListElement::createParentDir();
    appendOneFile(refListStore, parent);
}

void SinglePanel::appendOneFile(Glib::RefPtr<Gtk::ListStore> refListStore, FileListElement& oneNewDataElem) {
    FilesColumns filesColumns;
    Gtk::TreeModel::Row row = *(refListStore->append());
    
    row[filesColumns.file_name_column] = Glib::ustring(oneNewDataElem.getFileName());
    
    if (oneNewDataElem.getFileType() == FileType::REGULAR_FILE) {
        row[filesColumns.size_column] = oneNewDataElem.getFileSizeForDisplay();
    } else {
        row[filesColumns.size_column] = "<DIR>";
    }

    row[filesColumns.font_weight] = shouldBeBolded(oneNewDataElem) ? BOLDED_TXT : NOT_BOLDED_TXT;
}

bool SinglePanel::shouldBeBolded(const FileListElement &oneNewDataElem) const {
    const FileType &typeToCheck = oneNewDataElem.getFileType();
    return typeToCheck == FileType::DIRECTORY || typeToCheck == FileType::PARENT_DIR;
}

const Glib::ustring SinglePanel::getCurrentDir() const {
    return currentDir.toString();
}

void SinglePanel::onRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) {
    Preconditions::checkArgument(refListStore, "list store is completly empty");

    Glib::ustring selectedFileName = getSelectedFileName(path);
    currentDir.changeDirBy(selectedFileName);
    selectionHistory.changeDirBy(selectedFileName);

    gfm_debug("currently selected element is  %s\n", selectedFileName.c_str());
    gfm_debug("new file name is %s\n", currentDir.toString().c_str());
    this->updateCurrentDirHeader();

    //start reading
    createEmptyData();
    this->pathHeader->startProgress();
    startReadDataThread();
}

Glib::ustring SinglePanel::getSelectedFileName(const Gtk::TreeModel::Path &path) const {
    Gtk::TreeModel::iterator iter = refListStore->get_iter(path);
    Gtk::TreeRow selectedRow = *iter;

    FilesColumns filesColumns;
    Glib::ustring selectedFileName = selectedRow.get_value(filesColumns.file_name_column);
    return selectedFileName;
}

void SinglePanel::updateCurrentDirHeader() {
    this->pathHeader->setCurrentDir(currentDir.toString());
}

void SinglePanel::stopProgressIndicator() {
    this->pathHeader->stopProgress();
}

void SinglePanel::putFocusOnTopOfTreeview() {
    std::string selectionShouldBe = selectionHistory.getSelectionForDir(currentDir);
    auto foundPath = findByFileName(selectionShouldBe);
    gfm_debug("selection should be %s\n", selectionShouldBe.c_str());
    filesTreeView->set_cursor(foundPath);
}

const Gtk::TreeModel::Path SinglePanel::findByFileName(std::string fileNameToFind) {
    FilesColumns filesColumns;
    for (Gtk::TreeRow row : refListStore->children()) {
        const Glib::ustring &fileName = row->get_value(filesColumns.file_name_column);
        if (fileName == fileNameToFind) {
            return Gtk::TreePath(row);
        }
    }
    //first element in list
    return Gtk::TreePath("0");
}

void SinglePanel::onCursorChanged() {
    Gtk::TreeModel::Path path = filesTreeView->getHighlitedElement();
    Gtk::TreeModel::iterator iter = refListStore->get_iter(path);
    Gtk::TreeRow selectedRow = *iter;

    FilesColumns filesColumns;
    Glib::ustring selectedFileName = selectedRow.get_value(filesColumns.file_name_column);
    filePanelFooter.changeFooterValue(selectedFileName);
}
