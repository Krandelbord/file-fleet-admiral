#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include "Rectangle.h"
#include "FilesNavigationPanel.h"

class MainWindow : public Gtk::Window {
    public:
        MainWindow();
        void saveSettings() const;
    private:
        Rectangle getWindowSize() const;
        int getPanedPosition() const;
        FilesNavigationPanel *filesPanel;
};

#endif /** MAIN_WINDOW_H */

