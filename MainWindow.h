#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>

class MainWindow : public Gtk::Window {
    public:
        MainWindow();
    private:
        Gtk::Label m_label;
};

#endif /** MAIN_WINDOW_H */

