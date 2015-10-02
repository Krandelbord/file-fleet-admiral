#include "GuiReader.h"
#include "ThreadCalculation.h"
#include "config.h"

void GuiReader::commandReadThis(std::shared_ptr<ThreadMessage> msgToSendDataTo) {
    if (lastMessageSend) {
        //for the first work it is empty
        lastMessageSend->cancelWork();
    }
    this->lastMessageSend = msgToSendDataTo;

    ThreadCalculation threadObj;
    this->workerThread = Glib::Threads::Thread::create(
            sigc::bind(sigc::mem_fun(threadObj, &ThreadCalculation::threadFunction), lastMessageSend));
}

void GuiReader::waitForFinishWork() {
}

std::vector<FileListElement> GuiReader::executeCommandAndWaitForData(std::shared_ptr<ThreadMessage> msgToSendDataTo) {
    commandReadThis(msgToSendDataTo);
    waitForFinishWork();
    return lastMessageSend->getCaluclatedData();
}
