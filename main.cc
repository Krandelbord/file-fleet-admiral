#include "config.h"
#include "MainWindow.h"

int main(int argc, char **argv) {
    gfm_debug("starting gfm...\n");
    Gtk::Main app(&argc, &argv);

    MainWindow mainWindow;
    app.run(mainWindow);

    gfm_debug("saving config...\n");
    mainWindow.saveSettings();
    gfm_debug("ending gfm...\n");      
    return 0;
}

