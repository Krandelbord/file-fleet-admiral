#ifndef FILES_READ_WORKER_H
#define FILES_READ_WORKER_H

#include <glibmm.h>
#include "WorkerNotifable.h"
#include <vector>
/**
 * Thread that reads directory content 
 * **/
class FilesReadWorker {
    public:
        FilesReadWorker(const Glib::ustring& pathToRead);

        void threadFunction(WorkerNotifable* caller);
        const std::vector<Glib::ustring> getDataFromThread();
    private:
        Glib::ustring dirToRead;

        //mutex for data read/write
        mutable Glib::Threads::Mutex mutexForData;
        std::vector<Glib::ustring> fileDataRead;

        void initializeReturnData();
        void setNewData(const Glib::ustring& newData);

};
#endif /** FILES_READ_WORKER_H **/
