#include "ChownWindow.h"
#include <giomm/notification.h>
#include <giomm/application.h>
#include <gtkmm.h>

ChownWindow::ChownWindow() {
    Gtk::Dialog *dialog = Gtk::manage(new Gtk::Dialog("Chwon"));
    dialog->run();
}
