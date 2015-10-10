#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include <gtkmm.h>

class SettingsWindow : public Gtk::Dialog {
    public:
        SettingsWindow(Gtk::Window& parent);
};
#endif /** SETTINGS_WINDOW_H **/
