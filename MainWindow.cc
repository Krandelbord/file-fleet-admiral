#include "MainWindow.h"
#include "config.h"
#include "SinglePanel.h"

#define DO_NOT_EXPAND true
#define DO_NOT_FILL true

MainWindow::MainWindow() {
    this->set_position(Gtk::WIN_POS_CENTER);
    this->set_title(APPLICATION_NAME);
    

    Gtk::HBox* mainHbox = Gtk::manage(new Gtk::HBox());
    SinglePanel* leftPanel = Gtk::manage(new SinglePanel());

    mainHbox->pack_start(*leftPanel, DO_NOT_EXPAND, DO_NOT_FILL, 1);
    SinglePanel* rightPanel = Gtk::manage(new SinglePanel());
    mainHbox->pack_end(*rightPanel, DO_NOT_EXPAND, DO_NOT_FILL, 2);
    
    this->add(*mainHbox);
    this->show_all();
}

