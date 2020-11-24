
#include "KeyWithDescription.h"

KeyWithDescription::KeyWithDescription(KeyVerifier keyVerifier,
                                       Glib::ustring humanReadableShortcut,
                                       Glib::ustring description) {
    this->keyVerifier = keyVerifier;
    this->humanReadableShortcut = humanReadableShortcut;
    this->description = description;
}