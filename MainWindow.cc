#include "MainWindow.h"
#include "config.h"
#include "Settings.h"
#include "Rectangle.h"
#include "MenuBar.h"

MainWindow::MainWindow() {
    Settings settings;
    Rectangle winSizeFromCfg =  settings.readWindowSize();
    gfm_debug("Size read from cfg %d x %d \n", winSizeFromCfg.getWidth(), winSizeFromCfg.getHeight());
    this->set_default_size(winSizeFromCfg.getWidth(), winSizeFromCfg.getHeight());
    this->set_position(Gtk::WIN_POS_CENTER);
    this->set_title(APPLICATION_NAME);

    Gtk::Box *mainContainer = Gtk::manage(new Gtk::VBox());

    MenuBar *menuBar = Gtk::manage(new MenuBar());
    mainContainer->pack_start(*menuBar, Gtk::PackOptions::PACK_SHRINK);
 
    this->filesPanel = Gtk::manage(new FilesNavigationPanel(settings));
    mainContainer->add(*this->filesPanel);
    this->add(*mainContainer);
    this->show_all();
}

void MainWindow::saveSettings() const {
    Settings settings;
    Rectangle winSize = getWindowSize();
    gfm_debug("Window size is %d x %d\n", winSize.getWidth(), winSize.getHeight());
    settings.saveWindowSize(winSize);
    settings.savePanedPosition(this->getPanedPosition());

    settings.saveRightPanelDir(filesPanel->getRightPanelDir());
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

