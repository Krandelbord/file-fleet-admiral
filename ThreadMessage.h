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
        void addNewDataAsync(FileListElement newFileElement);

        const Glib::ustring getDirToRead();

        ~ThreadMessage();
    private:
        //mutex for data read/write
        mutable Glib::Threads::Mutex mutexForData;

        Glib::ustring dirToRead;
        std::vector<FileListElement> calculatedData;
};

#endif /** THREAD_MESSAGE_H **/
