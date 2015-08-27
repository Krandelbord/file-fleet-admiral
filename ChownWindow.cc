#include "ChownWindow.h"
#include <giomm/notification.h>
#include <giomm/application.h>
#include <gtkmm.h>

ChownWindow::ChownWindow(Gtk::Window& parentWin) 
    : Gtk::Dialog("chown window", parentWin) {
    this->run();
}
