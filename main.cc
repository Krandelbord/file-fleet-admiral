#include "config.h"
#include <iostream>
#include "MainWindow.h"

int main(int argc, char **argv) {
    gfm_debug("starting gfm...\n");
    Gtk::Main app(&argc, &argv);

    MainWindow mainWindow;
    app.run(mainWindow);

    gfm_debug("ending gfm...\n");      
    return 0;
}
