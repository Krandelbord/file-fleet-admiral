
#include "RenameExecutor.h"
#include "InterThreadProgressPipe.h"
#include "ThreadPerformingRename.h"

void RenameExecutor::executeRename(std::shared_ptr<InterThreadProgressPipe> threadCommunications,
                                   Glib::RefPtr<Gio::File> &originalFilePath, const Glib::ustring& aNewFileName) {
    ThreadPerformingRename threadObj;
    this->workerThread = Glib::Threads::Thread::create(
            sigc::bind(sigc::mem_fun(threadObj, &ThreadPerformingRename::threadFunction),
                       threadCommunications,
                       originalFilePath,
                       aNewFileName));
}
