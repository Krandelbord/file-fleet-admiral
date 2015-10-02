#include "ThreadMessage.h"
#include "config.h"

ThreadMessage::ThreadMessage(const Glib::ustring aDirToRead) {
    this->dirToRead = Glib::ustring(aDirToRead);
}

ThreadMessage::ThreadMessage(const PathResolver aDirToRead) {
    this->dirToRead = Glib::ustring(aDirToRead.toString());
}

void ThreadMessage::cancelWork() {
    gfm_debug("cancel work for dir %s\n", dirToRead.c_str());
}

std::vector<FileListElement> ThreadMessage::getCaluclatedData() {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    return calculatedData;
}

void ThreadMessage::addNewDataAsync(FileListElement newFileElement) {
   Glib::Threads::Mutex::Lock lock(mutexForData);
   gfm_debug("adding new FileListElement=%s\n", newFileElement.getFileName().c_str());
   calculatedData.push_back(newFileElement);
   
   lock.release();
}

const Glib::ustring ThreadMessage::getDirToRead() {
    return dirToRead;
}

void ThreadMessage::notifyAllThreadsOfWorkFinish() {
    dispatcherWorkFinished.emit();
}

void ThreadMessage::connectWorkFinishedSignal(const sigc::slot<void>& slot) {
    dispatcherWorkFinished.connect(slot);
}

ThreadMessage::~ThreadMessage() {
    gfm_debug("Destructor of ThreadMessage for %s\n", dirToRead.c_str());
}
