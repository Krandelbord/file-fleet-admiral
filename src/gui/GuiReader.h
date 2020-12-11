#ifndef GUI_READER_H
#define GUI_READER_H

#include "../ThreadMessage.h"
#include "file_panel/FileListElement.h"

/**
 * Class that belongs to gui thread responsible for reading DIR-content
 */
class GuiReader { 
    public:
        void commandReadThis(std::shared_ptr<ThreadMessage> msgToSendDataTo);
        void waitForFinishWork();
        std::vector<FileListElement> getCalculatedData();

        //synchronous method for reading data
        std::vector<FileListElement> executeCommandAndWaitForData(std::shared_ptr<ThreadMessage> msgToSendDataTo);
    private:
        std::shared_ptr<ThreadMessage> lastMessageSend;
        //actual thread where computation happens
        Glib::Threads::Thread* workerThread;
};

#endif /** GUI_READER_H **/
