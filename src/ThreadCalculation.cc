#include "ThreadCalculation.h"
#include <sys/stat.h>
#include "config.h"
#include "gui/SizeFormatterFactory.h"
#include "gui/FileWithInode.h"

auto ThreadCalculation::readFileSize(const std::string& filePathToReadSize) {
    struct stat_result {__off_t fileSizeInBytes; __ino_t inodeNumber;};
    struct stat statFile {};
    __off_t fileSize = 0;
    __ino_t inodeNumber = UNDEFINED_INODE;
    int err = stat(filePathToReadSize.c_str(), &statFile);
    if (err != 0) {
        fileSize = 0;
    } else {
        fileSize = statFile.st_size;
        inodeNumber = statFile.st_ino;
    }
    return stat_result{fileSize, inodeNumber};
}

void ThreadCalculation::threadFunction(std::shared_ptr<ThreadMessage> threadMessage) {
    const std::shared_ptr<SizeFormatter> sizeFormatter = SizeFormatterFactory::createFromConfig();
    Glib::ustring dirToRead = threadMessage->getDirToRead();
    int readPositionsCount = 0;

    std::vector<FileListElement> dirContent;
    //this is heavy work separate thread function
    if (Glib::file_test(dirToRead, Glib::FileTest::FILE_TEST_IS_DIR)) {
        Glib::Dir dir(dirToRead);
        for (Glib::DirIterator dirIter = dir.begin(); dirIter != dir.end(); ++dirIter) {
            std::string nextElemInDir = *dirIter;
            std::string path = Glib::build_filename(dirToRead, nextElemInDir);
            //Glib::usleep(101000);

            if (!nextElemInDir.empty()) {
                auto statData = readFileSize(path);
                FileType fileType = readFileType(path);
                const std::string formattedSize = sizeFormatter->formatSize(statData.fileSizeInBytes);
                dirContent.push_back(FileListElement(nextElemInDir, statData.fileSizeInBytes, fileType, formattedSize, statData.inodeNumber));
                readPositionsCount++;
            }
            if (threadMessage->shouldCancelWorkAsync()) {
                return;
            }
        }
    }
    threadMessage->getSortChain().sort(dirContent);
    threadMessage->addNewDataAsync(dirContent);
    threadMessage->notifyAllThreadsOfWorkFinish();
    gfm_debug("finish of calculation for dir %s, found %d\n", dirToRead.c_str(), readPositionsCount);
}


FileType ThreadCalculation::readFileType(const std::string& pathToReadFileType) {
    FileType fileType = FileType::REGULAR_FILE;
    if (Glib::file_test(pathToReadFileType, Glib::FILE_TEST_IS_DIR)) {
        fileType = FileType::DIRECTORY;
    }

    return fileType;
}

bool sortByNameDirsFirst(FileListElement first, FileListElement second) {
    //dirs first
    if (first.getFileType() == FileType::DIRECTORY && second.getFileType() == FileType::REGULAR_FILE) {
        return true;
    } else if (first.getFileType() == FileType::REGULAR_FILE && second.getFileType() == FileType::DIRECTORY) {
        return false;
    }
    return first.getFileName().lowercase() < second.getFileName().lowercase();
}

