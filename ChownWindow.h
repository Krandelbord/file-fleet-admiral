
#ifndef CHOWN_WINDOW_H
#define CHOWN_WINDOW_H

#include <gtkmm.h>

class ChownWindow : public Gtk::Dialog {
    public:
        ChownWindow(Gtk::Window& parentWin);
};
#endif /* CHOWN_WINDOW_H */
