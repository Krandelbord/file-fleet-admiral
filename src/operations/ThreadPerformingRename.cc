
#include "ThreadPerformingRename.h"
#include "../config.h"

void ThreadPerformingRename::threadFunction(std::shared_ptr<InterThreadProgressPipe> threadMessage,
                                            Glib::RefPtr<Gio::File> &originalFile,
                                            const Glib::ustring& newFileName) {
    if (newFileName == originalFile->get_basename()) {
        threadMessage->notifyWorkEnded();
        gfm_debug("new filename is same as original. No rename performed.\n");
        return;
    }
    threadMessage->updateProgress(0.1);
    bool fileExist = originalFile->query_exists(threadMessage->getCancellable());
    threadMessage->updateProgress(0.4);
    if (fileExist) {
        try {
            originalFile->set_display_name(newFileName, threadMessage->getCancellable());
        } catch (const Glib::Error& exc) {
            threadMessage->setMessage(exc.what());
            threadMessage->notifyWorkFailed();
            return;
        }
        threadMessage->updateProgress(1);
        threadMessage->notifyWorkEnded();
    } else {
        threadMessage->updateProgress(1);
        threadMessage->setMessage(_("File no longer exists"));
        threadMessage->notifyWorkFailed();
        //TODO refresh required
    }

}