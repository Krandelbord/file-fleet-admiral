
#ifndef FILE_FLEET_ADMIRAL_INTERTHREADPROGRESSPIPE_H
#define FILE_FLEET_ADMIRAL_INTERTHREADPROGRESSPIPE_H


#include <giomm.h>

class InterThreadProgressPipe {
public:
    void connectWorkFinishedSignal(const sigc::slot<void>& slot);
    void connectProgressUpdate(const sigc::slot<void>& slot);
    void connectWorkFailedSignal(const sigc::slot<void> &slot);
    bool shouldCancelWorkAsync();
    void cancelWork();
    void updateProgress(float newProgress);
    float getCurrentProgress();
    void notifyWorkEnded();
    void notifyWorkFailed();
    const Glib::RefPtr<Gio::Cancellable> &getCancellable() const;

    void setMessage(const Glib::ustring &message);
    const Glib::ustring &getMessage() const;
    bool isSuccess();
    bool isWorkEnded();

private:
    //inter-thread notifications
    Glib::Dispatcher dispatcherWorkFinished;
    Glib::Dispatcher dispatcherForProgressChange;
    Glib::Dispatcher dispatcherForFailure;
    Glib::RefPtr<Gio::Cancellable> cancellable = Gio::Cancellable::create();

    //mutex for data read/write - all data below are handled by this mutex
    mutable Glib::Threads::Mutex mutexForData;
    bool cancelWorkValue = false;
    bool workEnded = false;
    float progress;
    Glib::ustring message;
};


#endif //FILE_FLEET_ADMIRAL_INTERTHREADPROGRESSPIPE_H
