#ifndef THREAD_MESSAGE_H
#define THREAD_MESSAGE_H

#include <glibmm.h>
#include "FileListElement.h"

/**
 * Message send to thread what to execute, and to receive back information from worker thread.
 * It should have mutextx because all data can be read from multiple threads
 */
class ThreadMessage {
    public:
        ThreadMessage(const Glib::ustring aDirToRead);
        void cancelWork();
        std::vector<FileListElement> getCaluclatedData();

        ~ThreadMessage();
    private:
        Glib::ustring dirToRead;
};

#endif /** THREAD_MESSAGE_H **/
