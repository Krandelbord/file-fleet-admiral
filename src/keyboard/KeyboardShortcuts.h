#ifndef FILE_FLEET_ADMIRAL_KEYBOARDSHORTCUTS_H
#define FILE_FLEET_ADMIRAL_KEYBOARDSHORTCUTS_H


#include <gdk/gdkevents.h>
#include <memory>
#include <functional>
#include <glibmm/ustring.h>
#include <vector>
#include <set>
#include "KeyWithDescription.h"

class KeyboardShortcuts {
    typedef std::shared_ptr<std::function<bool(GdkEventKey)> > KeyVerifier;
private:
    std::vector<KeyWithDescription> handlers = std::vector<KeyWithDescription>();
    template <class Functor> KeyWithDescription createDelegate(Functor f, const Glib::ustring& readableShortcut,
                                                               const Glib::ustring& description);
public:
    KeyboardShortcuts();
    static bool isControlSPressed(const GdkEventKey key);
};


#endif //FILE_FLEET_ADMIRAL_KEYBOARDSHORTCUTS_H
