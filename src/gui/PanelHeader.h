#ifndef PANEL_HEADER_H
#define PANEL_HEADER_H
#include <gtkmm.h>

class PanelHeader : public Gtk::HBox {
    public:
        PanelHeader(const Glib::ustring& labelTxt);
        void setCurrentDir(const Glib::ustring& newLabel);
        void stopProgress();
        void startProgress();

    private:
        Gtk::Label headerLabel;
        Gtk::Spinner *spinner;
};

#endif /** PANEL_HEADER_H */
