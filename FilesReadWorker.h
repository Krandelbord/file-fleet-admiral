#ifndef FILES_READ_WORKER_H
#define FILES_READ_WORKER_H

#include <glibmm.h>
#include "WorkerNotifable.h"
#include "FileListElement.h"
#include <vector>
/**
 * Thread that reads directory content 
 * **/
class FilesReadWorker {
    public:
        FilesReadWorker(const Glib::ustring& pathToRead);

        void threadFunction(WorkerNotifable* caller);
        const std::vector<FileListElement> getDataFromThread();
    private:
        Glib::ustring dirToRead;

        //mutex for data read/write
        mutable Glib::Threads::Mutex mutexForData;
        std::vector<FileListElement> fileDataRead;

        void initializeReturnData();
        void setNewData(const FileListElement& newData);

};
#endif /** FILES_READ_WORKER_H **/
