#include "ThreadMessage.h"
#include "config.h"

ThreadMessage::ThreadMessage(const Glib::ustring aDirToRead) {
    this->dirToRead = Glib::ustring(aDirToRead);
}

void ThreadMessage::cancelWork() {
    gfm_debug("cancel work for dir %s\n", dirToRead.c_str());
}

std::vector<FileListElement> ThreadMessage::getCaluclatedData() {
    std::vector<FileListElement> dataReturned;
    dataReturned.push_back(FileListElement("someName", 123, FileType::DIRECTORY));
    return dataReturned;
}

ThreadMessage::~ThreadMessage() {
    gfm_debug("the desctructor of ThreadMessage\n");
    gfm_debug("Destructor of message for %s\n", dirToRead.c_str());
}
