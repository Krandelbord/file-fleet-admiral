#include <gdk/gdk.h>
#include "KeyboardShortcuts.h"
#include "KeyWithDescription.h"
#include "../config.h"

KeyboardShortcuts::KeyboardShortcuts() {
    handlers.push_back(createDelegate(KeyboardShortcuts::isControlSPressed, "Ctrl+S", _("Opens quick search")));
}

template <class Functor> KeyWithDescription KeyboardShortcuts::createDelegate(Functor f, const Glib::ustring& readableShortcut,
                                                                              const Glib::ustring& description) {
    return KeyWithDescription(KeyVerifier(new std::function<bool(GdkEventKey)>(f)), readableShortcut, description);
}

bool KeyboardShortcuts::isControlSPressed(const GdkEventKey key_event) {
    return key_event.state & GDK_CONTROL_MASK && (key_event.keyval == GDK_KEY_s || key_event.keyval == GDK_KEY_S);
}
