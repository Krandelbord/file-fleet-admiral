#ifndef SINGLE_PANEL_H
#define SINGLE_PANEL_H

#include <gtkmm.h>
#include "FilesReadWorker.h"
#include "FileListElement.h"
#include "PanelHeader.h"
#include "PathResolver.h"
#include "FilesTreeView.h"
#include "SelectionHistory.h"
#include "GuiReader.h"

/**
 * Represents single panel for files
**/
class SinglePanel : public Gtk::Frame {
    public:
        SinglePanel(const Glib::ustring& startDirPath);
        const Glib::ustring getCurrentDir() const;
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

        const Gtk::TreeModel::Path findByFileName(std::string fileNameToFind);

        GuiReader guiDataReader;
};

#endif /** SINGLE_PANEL_H */
