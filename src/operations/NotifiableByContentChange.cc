
#include "NotifiableByContentChange.h"

void NotifiableByContentChange::notifyRefreshDirs(const Glib::RefPtr<Gio::File> dirThatShouldBeRefreshed) {
    this->refreshDirViewSignal.emit(dirThatShouldBeRefreshed);
}
