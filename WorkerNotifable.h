#ifndef WORKER_NOTIFABLE_H
#define WORKER_NOTIFABLE_H

/**
 * Class that can be notifed by Worker (from another thread about new data
 */

class WorkerNotifable {
    public:
        // Called from the worker thread
        virtual void notifyNewDataFromThread() = 0;
};
#endif /** WORKER_NOTIFABLE_H **/
