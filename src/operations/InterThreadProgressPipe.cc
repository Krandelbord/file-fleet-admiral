
#include "InterThreadProgressPipe.h"


void InterThreadProgressPipe::connectWorkFinishedSignal(const sigc::slot<void>& slot) {
    dispatcherWorkFinished.connect(slot);
}

void InterThreadProgressPipe::connectWorkFailedSignal(const sigc::slot<void>& slot) {
    dispatcherForFailure.connect(slot);
}

void InterThreadProgressPipe::connectProgressUpdate(const sigc::slot<void>& slot) {
    dispatcherForProgressChange.connect(slot);
}

bool InterThreadProgressPipe::shouldCancelWorkAsync() {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    return cancelWorkValue;
}

void InterThreadProgressPipe::cancelWork() {
    cancellable->cancel(); //for canceling operations that supports Cancellable

    //for canceling custom-made loops
    Glib::Threads::Mutex::Lock lock(mutexForData);
    cancelWorkValue = true;
}

void InterThreadProgressPipe::updateProgress(float newProgress) {
    this->progress = newProgress;
    dispatcherForProgressChange.emit();
}

float InterThreadProgressPipe::getCurrentProgress() {
    return progress;
}

void InterThreadProgressPipe::notifyWorkEnded() {
    dispatcherWorkFinished.emit();
    Glib::Threads::Mutex::Lock lock(mutexForData);
    workEnded = true;
}

void InterThreadProgressPipe::notifyWorkFailed() {
    dispatcherForFailure.emit();
    Glib::Threads::Mutex::Lock lock(mutexForData);
    workEnded = true;
}

const Glib::RefPtr<Gio::Cancellable> &InterThreadProgressPipe::getCancellable() const {
    return cancellable;
}

const Glib::ustring &InterThreadProgressPipe::getMessage() const {
    return message;
}

void InterThreadProgressPipe::setMessage(const Glib::ustring &message) {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    InterThreadProgressPipe::message = message;
}

bool InterThreadProgressPipe::isWorkEnded() {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    return this->workEnded;
}
bool InterThreadProgressPipe::isSuccess() {
    Glib::Threads::Mutex::Lock lock(mutexForData);
    return message.empty();
}
