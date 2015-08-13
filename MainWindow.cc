#include "MainWindow.h"
#include "config.h"
#include "SinglePanel.h"
#include "Settings.h"
#include "Rectangle.h"

MainWindow::MainWindow() {
    Settings settings;
    Rectangle winSizeFromCfg =  settings.readWindowSize();
    gfm_debug("Size read from cfg %d x %d \n", winSizeFromCfg.getWidth(), winSizeFromCfg.getHeight());
    this->set_default_size(winSizeFromCfg.getWidth(), winSizeFromCfg.getHeight());
    this->set_position(Gtk::WIN_POS_CENTER);
    this->set_title(APPLICATION_NAME);
    

    Gtk::HPaned* mainHPaned = Gtk::manage(new Gtk::HPaned());
    SinglePanel* leftPanel = Gtk::manage(new SinglePanel());

    mainHPaned->add1(*leftPanel);
    SinglePanel* rightPanel = Gtk::manage(new SinglePanel());
    mainHPaned->add2(*rightPanel);
    
    this->add(*mainHPaned);
    this->show_all();
}

