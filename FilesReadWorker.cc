#include "FilesReadWorker.h"
#include "FileType.h"
#include "config.h"
#include <sys/stat.h>

bool sortByNameDirsFirst(FileListElement first, FileListElement second) {
    //dirs first
    if (first.getFileType() == FileType::DIRECTORY && second.getFileType() == FileType::REGULAR_FILE) {
        return true;
    } else if (first.getFileType() == FileType::REGULAR_FILE && second.getFileType() == FileType::DIRECTORY) {
        return false;
    }
    return first.getFileName().lowercase() < second.getFileName().lowercase();
}

FilesReadWorker::FilesReadWorker(const Glib::ustring& dirToRead, FilesSortType aSortType, WorkerNotifable* caller) {
    this->dirToRead = dirToRead; 
    this->sortType = aSortType;
    this->objectToNotifyChanges = caller;
    this->workerThread = Glib::Threads::Thread::create(sigc::mem_fun(this, &FilesReadWorker::threadFunction));
    // Connect the handler to the dispatcher.
}

void FilesReadWorker::threadFunction() {
    gfm_debug("Inside thread function \n");
  	Glib::Dir dir(dirToRead);
	for (Glib::DirIterator dirIter = dir.begin(); dirIter != dir.end(); ++dirIter) {

        std::string nextElemInDir = *dirIter;
        gfm_debug("nextElemInDir = %s\n", nextElemInDir.c_str());

		std::string path = Glib::build_filename(dirToRead, nextElemInDir);
		//Glib::usleep(101000);

		struct stat statFile;
        int m_fileSize = 0;
		int err = stat(path.c_str(), &statFile);
		if (err != 0) {
			m_fileSize = 0;
		} 
		m_fileSize = statFile.st_size;
	
		if (nextElemInDir.size() != 0)	{
            FileType fileType = FileType::REGULAR_FILE;
            if (Glib::file_test(path, Glib::FILE_TEST_IS_DIR)) {
                fileType = FileType::DIRECTORY;
            }
            setNewData(FileListElement(nextElemInDir, m_fileSize, fileType));
        }
	}
    std::sort(fileDataRead.begin(), fileDataRead.end(), sortByNameDirsFirst);
    objectToNotifyChanges->notifyNewDataFromThread();

    gfm_debug("before workerThread->join()\n");
    workerThread->join();
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
