#ifndef SINGLE_PANEL_H
#define SINGLE_PANEL_H

#include <gtkmm.h>
#include "FilesReadWorker.h"
#include "WorkerNotifable.h"

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
        Glib::ustring dirDisplayed;

        Gtk::Widget *pathHeader;
        Glib::RefPtr<Gtk::ListStore> refListStore;

        Gtk::TreeView* createFilesTreeView();
        Glib::RefPtr<Gtk::ListStore> createFakeData();
        void appendOneFile(Glib::RefPtr<Gtk::ListStore> refListStore, int size, const Glib::ustring& fileName);
        
        void onNewData();

        void startReadDataThread();
        Glib::Dispatcher m_Dispatcher;
        FilesReadWorker* readDirWorker;
        Glib::Threads::Thread* workerThread;
};

#endif /** SINGLE_PANEL_H */
