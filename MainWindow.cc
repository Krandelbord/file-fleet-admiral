#include "MainWindow.h"
#include "config.h"
#include "SinglePanel.h"
#include "Settings.h"
#include "Rectangle.h"

MainWindow::MainWindow() {
    Settings settings;
    Rectangle winSizeFromCfg =  settings.readWindowSize();
    this->set_default_size(winSizeFromCfg.getWidth(), winSizeFromCfg.getHeight());
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

