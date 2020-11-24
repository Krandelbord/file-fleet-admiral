#ifndef FILE_FLEET_ADMIRAL_KEYWITHDESCRIPTION_H
#define FILE_FLEET_ADMIRAL_KEYWITHDESCRIPTION_H


#include <gdk/gdk.h>
#include <memory>
#include <functional>
#include <glibmm/ustring.h>
#include <vector>
#include <set>

class KeyWithDescription {
    typedef std::shared_ptr<std::function<bool(GdkEventKey)> > KeyVerifier;
public:
    KeyWithDescription(KeyVerifier keyVerifier,
                       Glib::ustring humanReadableShortcut,
                       Glib::ustring description);

private:
    KeyVerifier keyVerifier;
    Glib::ustring description;
    Glib::ustring humanReadableShortcut;
};


#endif //FILE_FLEET_ADMIRAL_KEYWITHDESCRIPTION_H
