#ifndef SINGLE_PANEL_H
#define SINGLE_PANEL_H

#include <gtkmm.h>
#include "FilesReadWorker.h"
#include "WorkerNotifable.h"
#include "FileListElement.h"
#include "PanelHeader.h"
#include "PathResolver.h"
#include "FilesTreeView.h"

/**
 * Represents single panel for files
**/
class SinglePanel : public Gtk::Frame, public WorkerNotifable {
    public:
        SinglePanel(const Glib::ustring& startDirPath);
        const Glib::ustring getCurrentDir() const;

        // Called from the worker thread.
        void notifyNewDataFromThread();
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
        Glib::Dispatcher dispatcherNewData;
        std::shared_ptr<FilesReadWorker> readDirWorker;
        Glib::Threads::Thread* workerThread;

        void onRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
        Glib::ustring getSelectedFileName(const Gtk::TreeModel::Path &path) const;

        void stopProgressIndicator();

        bool shouldBeBolded(const FileListElement &oneNewDataElem) const;
        void putFocusOnTopOfTreeview();
};

#endif /** SINGLE_PANEL_H */
