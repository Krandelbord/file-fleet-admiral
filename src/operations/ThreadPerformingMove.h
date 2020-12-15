
#ifndef FILE_FLEET_ADMIRAL_THREADPERFORMINGMOVE_H
#define FILE_FLEET_ADMIRAL_THREADPERFORMINGMOVE_H

#include <memory>
#include "InterThreadProgressPipe.h"

class ThreadPerformingMove {
public:
    void threadFunction(std::shared_ptr<InterThreadProgressPipe> threadMessage,
                        Glib::RefPtr<Gio::File> &originalFile,
                        const Glib::ustring& destinationPath);

    private:
        void onMoveProgressing(goffset current, goffset total,
                               Glib::DateTime startTime,
                               std::shared_ptr<InterThreadProgressPipe> threadMessage);
};


#endif //FILE_FLEET_ADMIRAL_THREADPERFORMINGMOVE_H
