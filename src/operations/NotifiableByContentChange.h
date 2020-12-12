#ifndef FILE_FLEET_ADMIRAL_NOTIFIABLEBYCONTENTCHANGE_H
#define FILE_FLEET_ADMIRAL_NOTIFIABLEBYCONTENTCHANGE_H


#include <glibmm.h>
#include <giomm.h>

class NotifiableByContentChange {
public:
    void notifyRefreshDirs(Glib::RefPtr<Gio::File> dirThatShouldBeRefreshed);

protected:
    sigc::signal<void, Glib::RefPtr<Gio::File>> refreshDirViewSignal;
};


#endif //FILE_FLEET_ADMIRAL_NOTIFIABLEBYCONTENTCHANGE_H
