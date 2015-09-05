#ifndef SINGLE_PANEL_H
#define SINGLE_PANEL_H

#include <gtkmm.h>
#include "FilesReadWorker.h"
#include "WorkerNotifable.h"
#include "FileListElement.h"
#include "PanelHeader.h"

/**
 * Represents single panel for files
**/
class SinglePanel : public Gtk::Frame, public WorkerNotifable {
    public:
        SinglePanel(const Glib::ustring& startDirPath);
        const Glib::ustring& getCurrentDir() const;

        // Called from the worker thread.
        void notifyNewDataFromThread();
    private:
        void setCurrentDir(const Glib::ustring& newCurrentDir);

        Glib::ustring dirDisplayed;

        PanelHeader *pathHeader;
        Glib::RefPtr<Gtk::ListStore> refListStore;

        void createEmptyData();
        void appendOneFile(Glib::RefPtr<Gtk::ListStore> refListStore, FileListElement& oneNewDataElem);
        
        void onNewData();

        void startReadDataThread();
        Glib::Dispatcher m_Dispatcher;
        FilesReadWorker* readDirWorker;
        Glib::Threads::Thread* workerThread;

        void onRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
        Glib::ustring getSelectedFileName(const Gtk::TreeModel::Path &path) const;
};

#endif /** SINGLE_PANEL_H */
