#ifndef FILES_READ_WORKER_H
#define FILES_READ_WORKER_H

#include <vector>
#include <glibmm.h>
#include "WorkerNotifable.h"
#include "FileListElement.h"
#include "FilesSortType.h"
#include "config.h"
/**
 * Thread that reads directory content 
 * **/
class FilesReadWorker {
    public:
        FilesReadWorker(const Glib::ustring& pathToRead, FilesSortType sortType, WorkerNotifable* caller);
        virtual ~FilesReadWorker();

        void threadFunction(WorkerNotifable* caller);
        const std::vector<FileListElement> getDataFromThread();
    private:
        Glib::ustring dirToRead;
        FilesSortType sortType;

        //mutex for data read/write
        mutable Glib::Threads::Mutex mutexForData;
        std::vector<FileListElement> fileDataRead;
        //actual thread where computatation happens
        Glib::Threads::Thread* workerThread;

        void setNewData(const FileListElement& newData);

};
#endif /** FILES_READ_WORKER_H **/
