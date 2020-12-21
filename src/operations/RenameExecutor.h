
#ifndef FILE_FLEET_ADMIRAL_RENAMEEXECUTOR_H
#define FILE_FLEET_ADMIRAL_RENAMEEXECUTOR_H


#include "../ThreadMessage.h"
#include "InterThreadProgressPipe.h"
/**
 * Aka Worker
 */
class RenameExecutor {

public:
    void executeRename(std::shared_ptr<InterThreadProgressPipe> threadCommunications,
                       Glib::RefPtr<Gio::File> &originalFilePath,
                       const Glib::ustring &aNewFileName);
private:
    Glib::Threads::Thread *workerThread;
};


#endif //FILE_FLEET_ADMIRAL_RENAMEEXECUTOR_H
