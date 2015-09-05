#ifndef PANEL_HEADER_H
#define PANEL_HEADER_H
#include <gtkmm.h>

class PanelHeader : public Gtk::HBox {
    public:
        PanelHeader(const Glib::ustring& labelTxt);
        void setCurrentDir(const Glib::ustring& newLabel);

    private:
        Gtk::Label headerLabel;
};

#endif /** PANEL_HEADER_H */
