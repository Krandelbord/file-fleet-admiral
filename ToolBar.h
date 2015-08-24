#ifndef TOOL_BAR_H
#define TOOL_BAR_H

#include <gtkmm.h>

class ToolBar : public Gtk::Toolbar {
    public:
        ToolBar();

    private:
        void onChownClicked();
};

#endif /** TOOL_BAR_H */
