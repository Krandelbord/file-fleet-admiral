#include "FilesReadWorker.h"
#include "config.h"

FilesReadWorker::FilesReadWorker(const Glib::ustring& dirToRead) {
    this->dirToRead = dirToRead; 
}

void FilesReadWorker::threadFunction(WorkerNotifable* caller) {
    gfm_debug("Inside thread function \n");
    {
        Glib::Threads::Mutex::Lock lock(mutexForData);
        fileDataRead = "no data from thread so far";
    } // The mutex is unlocked here by lock's destructor.

    // Simulate a long calculation.
    for (int i = 0; ; ++i) // do until break
    {
        gfm_debug("one iteration start \n");
        Glib::usleep(250000); // microseconds

        Glib::Threads::Mutex::Lock lock(mutexForData);
        fileDataRead = "data from Thread "+dirToRead;
        lock.release();
        
        caller->notifyNewDataFromThread();
    }

    Glib::Threads::Mutex::Lock lock(mutexForData);
    lock.release();
    caller->notifyNewDataFromThread();
}

// Accesses to these data are synchronized by a mutex.
const Glib::ustring FilesReadWorker::getDataFromThread() const {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    return Glib::ustring(fileDataRead);
}
