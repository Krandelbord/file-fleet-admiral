#ifndef THREAD_MESSAGE_H
#define THREAD_MESSAGE_H

#include <glibmm.h>
#include "FileListElement.h"
#include "PathResolver.h"
#include "SortChain.h"

/**
 * Message send to thread what to execute, and to receive back information from worker thread.
 * It should have mutextx because all data can be read from multiple threads
 */
class ThreadMessage {
    public:
        ThreadMessage(const Glib::ustring aDirToRead, SortChain sortChain);
        ThreadMessage(const PathResolver aDirToRead, SortChain sortChain);

        void cancelWork();
        std::vector<FileListElement> getCaluclatedData();
        void addNewDataAsync(FileListElement newFileElement);
        void addNewDataAsync(std::vector<FileListElement> newFileElement);

        const Glib::ustring getDirToRead();
        void notifyAllThreadsOfWorkFinish();
        void connectWorkFinishedSignal(const sigc::slot<void>& slot);
        bool shouldCancelWorkAsync();
        SortChain getSortChain();

    ~ThreadMessage();
    private:
        //inter-thread notifications
        Glib::Dispatcher dispatcherWorkFinished;

        //mutex for data read/write - all data below are handled by this mutex
        mutable Glib::Threads::Mutex mutexForData;
        bool cancelWorkValue = false;
        Glib::ustring dirToRead;
        std::vector<FileListElement> calculatedData;
        SortChain sortChain;
};

#endif /** THREAD_MESSAGE_H **/
