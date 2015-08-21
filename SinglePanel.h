#ifndef SINGLE_PANEL_H
#define SINGLE_PANEL_H

#include <gtkmm.h>

/**
 * Represents single panel for files
**/
class SinglePanel : public Gtk::VBox {
    public:
        SinglePanel();
    private:
        Gtk::TreeView* createFilesTreeView();
        
};

#endif /** SINGLE_PANEL_H */
