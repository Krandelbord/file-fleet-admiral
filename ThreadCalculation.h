#ifndef THREAD_CALCULATION_H
#define THREAD_CALCULATION_H

#include <memory>
#include "ThreadMessage.h"

/**
 * Class that does havy computation is separate thread
 */
class ThreadCalculation {
    public:
        void threadFunction(std::shared_ptr<ThreadMessage> threadMessage);
};

#endif /** THREAD_CALCULATION_H */
