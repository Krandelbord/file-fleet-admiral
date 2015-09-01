#ifndef SINGLE_PANEL_H
#define SINGLE_PANEL_H

#include <gtkmm.h>
#include "FilesReadWorker.h"
#include "WorkerNotifable.h"
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

        Gtk::TreeView* createFilesTreeView();
        Glib::RefPtr<Gtk::ListStore> createFakeData();
        void appendOneFile(Glib::RefPtr<Gtk::ListStore> refListStore, int size, const Glib::ustring& fileName);
        
        void onNewData();

        void startReadDataThread();
        Glib::Dispatcher m_Dispatcher;
        FilesReadWorker* readDirWorker;
        Glib::Threads::Thread* workerThread;

        void onRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
};

#endif /** SINGLE_PANEL_H */
