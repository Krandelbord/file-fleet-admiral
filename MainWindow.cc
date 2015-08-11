#include "MainWindow.h"
#include "config.h"
#include "SinglePanel.h"

MainWindow::MainWindow() {
    this->set_position(Gtk::WIN_POS_CENTER);
    this->set_title(APPLICATION_NAME);
    
    SinglePanel singlePanel;
    Gtk::HBox mainHbox;
    this->add(mainHbox);
}
