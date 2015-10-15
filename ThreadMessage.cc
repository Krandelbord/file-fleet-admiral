#include "ThreadMessage.h"
#include "config.h"
#include <iostream>

ThreadMessage::ThreadMessage(const Glib::ustring aDirToRead, SortChain sortChainToUse) : sortChain(sortChainToUse) {
    dirToRead = Glib::ustring(aDirToRead);
}

ThreadMessage::ThreadMessage(const PathResolver aDirToRead, SortChain sortChainToUse) : sortChain(sortChainToUse) {
    dirToRead = Glib::ustring(aDirToRead.toString());
}

void ThreadMessage::cancelWork() {
    gfm_debug("cancel work for dir %s\n", dirToRead.c_str());
    Glib::Threads::Mutex::Lock lock(mutexForData);
    this->cancelWorkValue = true;
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

void ThreadMessage::addNewDataAsync(std::vector<FileListElement> newFileElements) {
   Glib::Threads::Mutex::Lock lock(mutexForData);
   gfm_debug("adding bunch of file elements\n");
   for (auto newElem : newFileElements) {
       calculatedData.push_back(newElem);
   }
   
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

bool ThreadMessage::shouldCancelWorkAsync() {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    return cancelWorkValue;
}

SortChain ThreadMessage::getSortChain() {
    return this->sortChain;
}

ThreadMessage::~ThreadMessage() {
    gfm_debug("Destructor of ThreadMessage for %s\n", dirToRead.c_str());
}
