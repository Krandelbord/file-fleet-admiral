#include "ThreadCalculation.h"
#include "config.h"

void ThreadCalculation::threadFunction(std::shared_ptr<ThreadMessage> threadMessage) {
    //this is heavy work spearate thread function
    Glib::usleep(101000);
    gfm_debug("finish of calculation \n");
}

