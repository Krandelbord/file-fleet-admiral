#include <vector>
#include <memory>
#include "SinglePanel.h"
#include "FilesColumns.h"
#include "../../config.h"
#include "../../Preconditions.h"
#include "../../sort/CompareBySize.h"
#include "../../sort/CompareDirsFirst.h"
#include "../RenamePopup.h"
#include "../../viewer/FileViewer.h"

#define PANEL_MARGIN_SIZE 5
#define NOT_BOLDED_TXT 400
#define BOLDED_TXT (2*NOT_BOLDED_TXT)

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
    //signal launched after GUI is rendered
    Glib::signal_idle().connect(
            sigc::bind_return(sigc::mem_fun(*this, &SinglePanel::startReadDataThread), false));
    this->signal_key_press_event().connect(sigc::mem_fun(*this, &SinglePanel::onKeyPressed));
    this->filePanelFooter.signalOnQuickSearchChanged().connect(sigc::mem_fun(*this, &SinglePanel::onQuickSearchQueryReceived));
    this->filePanelFooter.signalOnSearchNext().connect(sigc::mem_fun(*this, &SinglePanel::moveCursorToNextMatch));
    this->filePanelFooter.signalOnEnterPressedInQuickSearch().connect(sigc::mem_fun(*this, &SinglePanel::onEnterForQuickSearch));
    this->filePanelFooter.signalOnQuickSearchClosed().connect(sigc::mem_fun(*this, &SinglePanel::onQuickSearchClosed));
}

void SinglePanel::startReadDataThread() {
    gfm_debug("reading files data starts here\n");

    SortChain sortChain(std::make_shared<CompareDirsFirst>());
    sortChain.addSorting(std::make_shared<CompareBySize>());
    std::shared_ptr<ThreadMessage> threadMsng = std::make_shared<ThreadMessage>(currentDir, sortChain);
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
    row[filesColumns.file_type] = oneNewDataElem.getFileType();
    if (oneNewDataElem.getFileType() == FileType::REGULAR_FILE) {
        row[filesColumns.size_column] = oneNewDataElem.getFileSizeForDisplay();
    } else {
        row[filesColumns.size_column] = "<DIR>";
    }

    row[filesColumns.font_weight] = shouldBeBolded(oneNewDataElem) ? BOLDED_TXT : NOT_BOLDED_TXT;
    row[filesColumns.inodeNumber] = oneNewDataElem.getInodeNumber();
    if (oneNewDataElem.getIcon())
        row[filesColumns.icon] = oneNewDataElem.getIcon()->copy();
}

bool SinglePanel::shouldBeBolded(const FileListElement &oneNewDataElem) const {
    const FileType &typeToCheck = oneNewDataElem.getFileType();
    return typeToCheck == FileType::DIRECTORY || typeToCheck == FileType::PARENT_DIR;
}

Glib::ustring SinglePanel::getCurrentDir() const {
    return currentDir.toString();
}

void SinglePanel::onRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) {
    FileType type = getCurrentFileType(path);
    if (type == FileType::DIRECTORY || type == FileType::PARENT_DIR) {
        changeDirectory(path);
    } else {
        FileViewer fileViewer(getCurrentDir(), getSelectedFileName(path));
        fileViewer.show();
    }
}

FileType SinglePanel::getCurrentFileType(const Gtk::TreeModel::Path &path) {
    Gtk::TreeModel::iterator selectedRow = refListStore->get_iter(path);
    FilesColumns columns;
    FileType type = selectedRow->get_value(columns.file_type);
    return type;
}
void SinglePanel::refreshCurrentDir() {
    createEmptyData();
    pathHeader->startProgress();
    startReadDataThread();
}

void SinglePanel::changeDirectory(const Gtk::TreeModel::Path &path) {
    Preconditions::checkArgument(refListStore.get() != nullptr, "list store is completely empty");
    Glib::ustring selectedFileName = getSelectedFileName(path);
    changeDirByPath(selectedFileName);
}

void SinglePanel::changeDirByPath(const Glib::ustring &selectedFileName) {
    gfm_debug("currently selected element is  %s\n", selectedFileName.c_str());
    currentDir.changeDirBy(selectedFileName);
    selectionHistory.changeDirBy(selectedFileName);
    gfm_debug("new file name is %s\n", currentDir.toString().c_str());
    updateCurrentDirHeader();

    //start reading
    createEmptyData();
    pathHeader->startProgress();
    startReadDataThread();
}

Glib::ustring SinglePanel::getSelectedFileName(const Gtk::TreeModel::Path &path) const {
    Gtk::TreeModel::iterator iter = refListStore->get_iter(path);
    Gtk::TreeRow selectedRow = *iter;

    FilesColumns filesColumns;
    Glib::ustring selectedFileName = iter->get_value(filesColumns.file_name_column);

    return selectedFileName;
}

void SinglePanel::updateCurrentDirHeader() {
    this->pathHeader->setCurrentDir(currentDir.toString());
}

void SinglePanel::stopProgressIndicator() {
    this->pathHeader->stopProgress();
}

void SinglePanel::putFocusOnTopOfTreeview() {
    FileWithInode selectionShouldBe = selectionHistory.getSelectionForDir(currentDir);
    gfm_debug("Cursor should be put on %s\n", selectionShouldBe.toString().c_str());
    auto foundPath = findByInodeOrName(selectionShouldBe);
    if (foundPath) {
        filesTreeView->set_cursor(foundPath);
    } else {
        filesTreeView->set_cursor(firstElementOnList());
    }
}

const Gtk::TreeModel::Path SinglePanel::findByFileNameWithFunc(Glib::ustring fileNameToFind,
                                                               bool (*findFunction)(Glib::ustring, Glib::ustring),
                                                               const Gtk::TreeModel::Path afterElement) {
    FilesColumns filesColumns;

    Gtk::TreeModel::iterator szmo = Gtk::TreeModel::iterator();
    if (!afterElement.empty()) {
        szmo = refListStore->get_iter(afterElement);
        gfm_debug("We do quick search after %s\n", szmo->get_value(filesColumns.file_name_column).c_str());
    }
    bool weAreAfterElement = afterElement.empty();
    for (Gtk::TreeRow row : refListStore->children()) {
        const Glib::ustring &fileName = row->get_value(filesColumns.file_name_column);
        gfm_debug("Iterating in tree [%d] view over %s\n", weAreAfterElement, fileName.c_str());
        if (weAreAfterElement) {
            if (findFunction(fileName, fileNameToFind)) {
                gfm_debug("Found match fileNameToFind=„%s” with fileNameToFind=„%s” compare_result=%ld\n", fileNameToFind.c_str(),
                          fileName.c_str(), fileName.find_first_of(fileNameToFind));
                return Gtk::TreePath(row);
            }
        }
        if (!afterElement.empty() && row == szmo) {
            gfm_debug("Switch weAreAfterElement = true\n");
            weAreAfterElement = true;
        }
    }
    //first element in list
    return firstElementOnList();
}

Gtk::TreePath SinglePanel::firstElementOnList() const { return Gtk::TreePath("0"); }

Gtk::TreeModel::Path SinglePanel::findByFileNameStartingWith(const std::string& fileNameToFind, const Gtk::TreeModel::Path& afterElement) {
    return this->findByFileNameWithFunc(fileNameToFind, [](Glib::ustring a, Glib::ustring b) {return a.find(b)==0;}, afterElement) ;
}

Gtk::TreeModel::Path SinglePanel::findByInodeOrName(FileWithInode fileToFind) {
    const Gtk::TreePath &inodeSearchResult = findByInodeNumber(fileToFind);
    if (inodeSearchResult.empty()) {
        return findByExactFileName(fileToFind.getFileName());
    } else {
        return inodeSearchResult;
    }
}

Gtk::TreePath SinglePanel::findByInodeNumber(const FileWithInode &fileNameToFind) {
    FilesColumns filesColumns;
    for (const Gtk::TreeRow& fileListRow : refListStore->children()) {
        __ino_t inodeNumber = fileListRow->get_value(filesColumns.inodeNumber);
        if (fileNameToFind.matchesInode(inodeNumber)) {
            return Gtk::TreePath(fileListRow);
        }
    }
    // empty
    return Gtk::TreePath();
}

Gtk::TreeModel::Path SinglePanel::findByExactFileName(std::string fileNameToFind) {
    return this->findByFileNameWithFunc(fileNameToFind, [](Glib::ustring a, Glib::ustring b) {return a.compare(b)==0;}, Gtk::TreeModel::Path()) ;
}

void SinglePanel::onCursorChanged() {
    Glib::ustring selectedFileName = getSelectedFileName();
    if (!selectedFileName.empty()) {
        filePanelFooter.changeFooterValue(selectedFileName);
    }
}

Gtk::TreeRow SinglePanel::getFileUnderCursor() {
    Glib::ustring selectedFileName;
    Gtk::TreeModel::Path path = filesTreeView->getHighlitedElement();
    if (!path.empty()) {
        Gtk::TreeModel::iterator iter = refListStore->get_iter(path);
        return *iter;
    }
    return {};
}

Glib::ustring SinglePanel::getSelectedFileName() {
    Glib::ustring selectedFileName;
    Gtk::TreeModel::Path path = filesTreeView->getHighlitedElement();
    if (!path.empty()) {
        Gtk::TreeModel::iterator iter = refListStore->get_iter(path);
        Gtk::TreeRow selectedRow = *iter;

        FilesColumns filesColumns;
        selectedFileName = selectedRow.get_value(filesColumns.file_name_column);
    }
    return selectedFileName;
}

bool SinglePanel::onKeyPressed(const GdkEventKey *key_event) {
    gfm_debug("Key pressed inside panel: %s = keyval(%x)\n", key_event->string, key_event->keyval);

    if (isControlHolded(key_event) && (key_event->keyval == GDK_KEY_s || key_event->keyval == GDK_KEY_S)) {
        gfm_debug("This is ctrl+s\n");
        this->showQuickSearch();
        return true;
    }
    if (!isShiftHolded(key_event) && key_event->keyval == GDK_KEY_F6) {
        gfm_debug("F6 Pressed\n");
        const Glib::RefPtr<Gio::File>& movedFile = Gio::File::create_for_path(
                Glib::build_filename(getCurrentDir(), getSelectedFileName()));
        showMoveSignal.emit(movedFile);
        return true;
    }
    if (isShiftHolded(key_event) && key_event->keyval == GDK_KEY_F6) {
        gfm_debug("Shift+F6 Pressed\n");

        FileWithInode ff = toFileWithInode(getFileUnderCursor());
        selectionHistory.updateForCurrentDir(getCurrentDir(), ff);
        showRenameSignal.emit(getCurrentDir(), getSelectedFileName());
        return true;
    }
    return false;
}

guint SinglePanel::isControlHolded(const GdkEventKey *key_event) const { return key_event->state & GDK_CONTROL_MASK; }
bool SinglePanel::isShiftHolded(const GdkEventKey *key_event) const { return key_event->state & GDK_SHIFT_MASK; }


void SinglePanel::showQuickSearch() {
    filePanelFooter.showQuickSearch();
}

void SinglePanel::moveCursorToNextMatch(Glib::ustring quickSearchValue) {
    const Gtk::TreeModel::Path &currentElement = filesTreeView->getHighlitedElement();
    Gtk::TreeModel::Path nextPathFound = this->findByFileNameStartingWith(quickSearchValue, currentElement);
    if (!nextPathFound.empty()) {
        filesTreeView->set_cursor(nextPathFound);
        filesTreeView->markRowActive(nextPathFound);
    }
}

void SinglePanel::onQuickSearchQueryReceived(Glib::ustring quickSearchValue) {
    gfm_debug("Quick search query %s\n", quickSearchValue.c_str());
    auto foundPath = this->findByFileNameStartingWith(quickSearchValue, Gtk::TreeModel::Path());
    filesTreeView->set_cursor(foundPath);
    filesTreeView->markRowActive(foundPath);
}

void SinglePanel::onEnterForQuickSearch(Glib::ustring quickSearchValue) {
    const Gtk::TreeModel::Path &currentElement = filesTreeView->getHighlitedElement();
    if (!currentElement.empty()) {
        this->changeDirectory(currentElement);
        filesTreeView->grab_focus();
    }
}

void SinglePanel::onQuickSearchClosed() {
    filesTreeView->grab_focus();
}

sigc::signal<void, Glib::ustring, Glib::ustring> SinglePanel::signalShowRename() {
    return this->showRenameSignal;
}

FileWithInode SinglePanel::toFileWithInode(Gtk::TreeRow row) {
    FilesColumns possibleColumns;
    return FileWithInode(row[possibleColumns.file_name_column], row[possibleColumns.inodeNumber]);
}

sigc::signal<void, const Glib::RefPtr<Gio::File>&> SinglePanel::signalShowMoveFile() {
    return this->showMoveSignal;
}