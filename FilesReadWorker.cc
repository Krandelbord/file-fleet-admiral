#include "FilesReadWorker.h"
#include "config.h"
#include <sys/stat.h>

FilesReadWorker::FilesReadWorker(const Glib::ustring& dirToRead) {
    this->dirToRead = dirToRead; 
}

void FilesReadWorker::threadFunction(WorkerNotifable* caller) {
    gfm_debug("Inside thread function \n");
  	Glib::Dir dir(dirToRead);
	for (Glib::DirIterator dirIter = dir.begin(); dirIter != dir.end(); ++dirIter) {

        std::string nextElemInDir = *dirIter;
        gfm_debug("nextElemInDir = %s\n", nextElemInDir.c_str());
  	
		if (nextElemInDir.size() != 0)	{
            setNewData(nextElemInDir);
            caller->notifyNewDataFromThread();
        }
	}
    gfm_debug("koniec plik byl\n");
    //caller->notifyNewDataFromThread();
}

void FilesReadWorker::setNewData(const Glib::ustring& newData) {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    gfm_debug("set new data with %s\n", newData.c_str());
    fileDataRead.push_back(Glib::ustring(newData));
    // The mutex is unlocked here by lock's destructor.
}

// Accesses to these data are synchronized by a mutex.
const std::vector<Glib::ustring> FilesReadWorker::getDataFromThread() {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    std::vector<Glib::ustring> copyToReturn = fileDataRead;
    fileDataRead.clear(); //empty output quueue
    return copyToReturn;
}
