#include "FilesReadWorker.h"
#include "config.h"

FilesReadWorker::FilesReadWorker(const Glib::ustring& dirToRead) {
    this->dirToRead = dirToRead; 
}

void FilesReadWorker::threadFunction(WorkerNotifable* caller) {
    gfm_debug("Inside thread function \n");
    initializeReturnData();

    // Simulate a long calculation.
    for (int i = 0; ; ++i) // do until break
    {
        gfm_debug("one iteration start \n");
        Glib::usleep(250000); // microseconds

        setNewData("data from thread");        
        caller->notifyNewDataFromThread();
    }
    caller->notifyNewDataFromThread();
}

void FilesReadWorker::initializeReturnData() {
    setNewData("");
}

void FilesReadWorker::setNewData(const Glib::ustring& newData) {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    fileDataRead = Glib::ustring(newData);
    // The mutex is unlocked here by lock's destructor.
}

// Accesses to these data are synchronized by a mutex.
const Glib::ustring FilesReadWorker::getDataFromThread() const {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    return Glib::ustring(fileDataRead);
}
