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

void MainWindow::saveSettings() const {
    Settings settings;
    int width_read, height_read;
    this->get_size(width_read, height_read);
    gfm_debug("Window size is %d x %d\n", width_read, height_read);
    settings.saveWindowSize(width_read);
}
