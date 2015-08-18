#include "MainWindow.h"
#include "config.h"
#include "Settings.h"
#include "Rectangle.h"

MainWindow::MainWindow() {
    Settings settings;
    Rectangle winSizeFromCfg =  settings.readWindowSize();
    gfm_debug("Size read from cfg %d x %d \n", winSizeFromCfg.getWidth(), winSizeFromCfg.getHeight());
    this->set_default_size(winSizeFromCfg.getWidth(), winSizeFromCfg.getHeight());
    this->set_position(Gtk::WIN_POS_CENTER);
    this->set_title(APPLICATION_NAME);
    
    this->filesPanel = Gtk::manage(new FilesNavigationPanel(settings));
    Gtk::HBox *mainHBox = Gtk::manage(new Gtk::HBox());
    mainHBox->add(*this->filesPanel);
    this->add(*mainHBox);
    this->show_all();
}

void MainWindow::saveSettings() const {
    Settings settings;
    Rectangle winSize = getWindowSize();
    gfm_debug("Window size is %d x %d\n", winSize.getWidth(), winSize.getHeight());
    settings.saveWindowSize(winSize);
    settings.savePanedPosition(this->getPanedPosition());
}

Rectangle MainWindow::getWindowSize() const {
    int width_read, height_read;
    this->get_size(width_read, height_read);
    Rectangle winSizeRect = Rectangle(width_read, height_read);
    return winSizeRect;
}

int MainWindow::getPanedPosition() const {
   const Gtk::HPaned *panedInside = (const Gtk::HPaned*) filesPanel;
   return panedInside->get_position();
}

