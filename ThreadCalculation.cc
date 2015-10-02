#include "ThreadCalculation.h"
#include <sys/stat.h>
#include "config.h"

void ThreadCalculation::threadFunction(std::shared_ptr<ThreadMessage> threadMessage) {
    Glib::ustring dirToRead = threadMessage->getDirToRead();
    //this is heavy work spearate thread function
    if (!Glib::file_test(dirToRead, Glib::FileTest::FILE_TEST_IS_DIR)) {
        //threadMessage->notifyNewDataFromThread();
        return;
    }
  	
    Glib::Dir dir(dirToRead);
    int readPositionsCount = 0;
	for (Glib::DirIterator dirIter = dir.begin(); dirIter != dir.end(); ++dirIter) {
        std::string nextElemInDir = *dirIter;
		std::string path = Glib::build_filename(dirToRead, nextElemInDir);
		Glib::usleep(101000);

        if (nextElemInDir.size()!=0) {
            __off_t sizeInBytes = readFileSize(path);
            FileType fileType = readFileType(path);
            threadMessage->addNewDataAsync(FileListElement(nextElemInDir, sizeInBytes, fileType));
            readPositionsCount++;
        }
    }

    threadMessage->notifyAllThreadsOfWorkFinish();
    gfm_debug("finish of calculation for dir %s, found %d\n", dirToRead.c_str(), readPositionsCount);
}

__off_t ThreadCalculation::readFileSize(const std::string& filePathToReadSize) {
    struct stat statFile;
    __off_t fileSize = 0;
    int err = stat(filePathToReadSize.c_str(), &statFile);
    if (err != 0) {
        fileSize = 0;
    } else {
        fileSize = statFile.st_size;
    }
    return fileSize;
}

FileType ThreadCalculation::readFileType(const std::string& pathToReadFileType) {
    FileType fileType = FileType::REGULAR_FILE;
    if (Glib::file_test(pathToReadFileType, Glib::FILE_TEST_IS_DIR)) {
        fileType = FileType::DIRECTORY;
    }

    return fileType;
}
