#ifndef SINGLE_PANEL_H
#define SINGLE_PANEL_H

#include <gtkmm.h>
#include "FileListElement.h"
#include "../PanelHeader.h"
#include "../PathResolver.h"
#include "FilesTreeView.h"
#include "../SelectionHistory.h"
#include "../GuiReader.h"
#include "FilePanelFooter.h"

/**
 * Represents single panel for files
**/
class SinglePanel : public Gtk::Frame {
    public:
        SinglePanel(const Glib::ustring& startDirPath);
        Glib::ustring getCurrentDir() const;
    private:
        void updateCurrentDirHeader();

        PathResolver currentDir;

        PanelHeader *pathHeader;
        Glib::RefPtr<Gtk::ListStore> refListStore;
        FilesTreeView *filesTreeView;

        void createEmptyData();
        void appendOneFile(Glib::RefPtr<Gtk::ListStore> refListStore, FileListElement& oneNewDataElem);

        void onNewData();

        void startReadDataThread();

        void onRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
        Glib::ustring getSelectedFileName(const Gtk::TreeModel::Path &path) const;
        SelectionHistory selectionHistory;

        void stopProgressIndicator();

        bool shouldBeBolded(const FileListElement &oneNewDataElem) const;
        void putFocusOnTopOfTreeview();

        FilePanelFooter filePanelFooter;

        GuiReader guiDataReader;

        void onCursorChanged();

        bool onKeyPressed(const GdkEventKey *key_event);

        guint isControlHolded(const GdkEventKey *key_event) const;

        void showQuickSearch();

        void onQuickSearchQueryReceived(const Glib::ustring& quickSearchValue);
        void moveCursorToNextMatch(const Glib::ustring& quickSearchValue);
        void onEnterForQuickSearch(const Glib::ustring& quickSearchValue);
        void onQuickSearchClosed();

        Gtk::TreeModel::Path findByExactFileName(std::string fileNameToFind);
        Gtk::TreeModel::Path findByFileNameStartingWith(const std::string& fileNameToFind, const Gtk::TreeModel::Path& afterElement);
        const Gtk::TreeModel::Path findByFileNameWithFunc(Glib::ustring basic_string, bool (*findFunction)(Glib::ustring, Glib::ustring),
                                                          const Gtk::TreeModel::Path afterElement);

    void changeDirectory(const Gtk::TreeModel::Path &path);
};

#endif /** SINGLE_PANEL_H */
