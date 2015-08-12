#include "MainWindow.h"
#include "config.h"
#include "SinglePanel.h"
#include "Settings.h"

#define DO_NOT_EXPAND true
#define DO_NOT_FILL true

MainWindow::MainWindow() {
    Settings settings;
    int winSize =  settings.readWindowSize();
    this->set_default_size(winSize, winSize*1.2);
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

