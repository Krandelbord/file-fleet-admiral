#include "MainWindow.h"
#include "config.h"
#include "SinglePanel.h"

#define DO_NOT_EXPAND true
#define DO_NOT_FILL true

MainWindow::MainWindow() {
    this->set_position(Gtk::WIN_POS_CENTER);
    this->set_title(APPLICATION_NAME);
    

    Gtk::HPaned* mainHbox = Gtk::manage(new Gtk::HPaned());
    SinglePanel* leftPanel = Gtk::manage(new SinglePanel());

    mainHbox->add1(*leftPanel);
    SinglePanel* rightPanel = Gtk::manage(new SinglePanel());
    mainHbox->add2(*rightPanel);
    
    this->add(*mainHbox);
    this->show_all();
}

