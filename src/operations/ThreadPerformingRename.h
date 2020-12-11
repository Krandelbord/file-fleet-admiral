
#ifndef FILE_FLEET_ADMIRAL_THREADPERFORMINGRENAME_H
#define FILE_FLEET_ADMIRAL_THREADPERFORMINGRENAME_H


#include <memory>
#include "InterThreadProgressPipe.h"

class ThreadPerformingRename {
    public:
        void threadFunction(std::shared_ptr<InterThreadProgressPipe> threadMessage,
                            Glib::RefPtr<Gio::File> &originalFile,
                            const Glib::ustring& newFileName);
};

#endif //FILE_FLEET_ADMIRAL_THREADPERFORMINGRENAME_H
