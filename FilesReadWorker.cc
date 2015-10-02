#include "FilesReadWorker.h"
#include "config.h"
#include <sys/stat.h>
#include <iostream>



FilesReadWorker::FilesReadWorker(const Glib::ustring& dirToRead, FilesSortType aSortType) {
    this->dirToRead = Glib::ustring(dirToRead); 
    this->sortType = aSortType;
}

void FilesReadWorker::threadFunction() {
    gfm_debug("Inside thread function for dir %s \n", dirToRead.c_str());
    if (!Glib::file_test(dirToRead, Glib::FileTest::FILE_TEST_IS_DIR)) {
        return;
    }
  	Glib::Dir dir(dirToRead);
	for (Glib::DirIterator dirIter = dir.begin(); dirIter != dir.end(); ++dirIter) {
        std::string nextElemInDir = *dirIter;
		std::string path = Glib::build_filename(dirToRead, nextElemInDir);
		Glib::usleep(101000);

		struct stat statFile;
        __off_t m_fileSize = 0;
		int err = stat(path.c_str(), &statFile);
		if (err != 0) {
			m_fileSize = 0;
		} else {
            m_fileSize = statFile.st_size;
        }
	
		if (nextElemInDir.size() != 0)	{
            FileType fileType = FileType::REGULAR_FILE;
            if (Glib::file_test(path, Glib::FILE_TEST_IS_DIR)) {
                fileType = FileType::DIRECTORY;
            }
            setNewData(FileListElement(nextElemInDir, m_fileSize, fileType));
        }
	}
    
    gfm_debug("End of reading thread for dir %s\n", dirToRead.c_str());
}

void FilesReadWorker::setNewData(const FileListElement& newData) {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    fileDataRead.push_back(FileListElement(newData));
    // The mutex is unlocked here by lock's destructor.
}

// Accesses to these data are synchronized by a mutex.
const std::vector<FileListElement> FilesReadWorker::getDataFromThread() {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    std::vector<FileListElement> copyToReturn = fileDataRead;
    fileDataRead.clear(); //empty output queue
    return copyToReturn;
}

FilesReadWorker::~FilesReadWorker() {
    std::cout << "Destructor of files read worker for dir " << std::endl;
}

