#include "ThreadCalculation.h"
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
		//Glib::usleep(101000);
        threadMessage->addNewDataAsync(FileListElement(nextElemInDir, 0, FileType::DIRECTORY));
        readPositionsCount++;
    }
    gfm_debug("finish of calculation for dir %s, found %d\n", dirToRead.c_str(), readPositionsCount);
}

