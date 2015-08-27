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

		std::string path = Glib::build_filename(dirToRead, nextElemInDir);
		//Glib::usleep(101000);

		//bool isDir = Glib::file_test(path, Glib::FILE_TEST_IS_DIR);

		struct stat statFile;
        int m_fileSize = 0;
		int err = stat(path.c_str(), &statFile);
		if (err != 0) {
			m_fileSize = 0;
		} 
		m_fileSize = statFile.st_size;
	
		if (nextElemInDir.size() != 0)	{
            setNewData(FileListElement(nextElemInDir, m_fileSize));
            caller->notifyNewDataFromThread();
        }
	}
    gfm_debug("End of reading thread\n");
}

void FilesReadWorker::setNewData(const FileListElement& newData) {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    gfm_debug("set new data with %s\n", newData.getFileName().c_str());
    fileDataRead.push_back(FileListElement(newData));
    // The mutex is unlocked here by lock's destructor.
}

// Accesses to these data are synchronized by a mutex.
const std::vector<FileListElement> FilesReadWorker::getDataFromThread() {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    std::vector<FileListElement> copyToReturn = fileDataRead;
    fileDataRead.clear(); //empty output quueue
    return copyToReturn;
}
