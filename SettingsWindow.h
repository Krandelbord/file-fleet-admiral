#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include <gtkmm.h>

class SettingsWindow : public Gtk::Dialog {
    public:
        SettingsWindow(Gtk::Window& parent);

    private:
        Gtk::Button* addImageButton(const Glib::ustring &iconName, const Glib::ustring& label);
        void onSaveClicked(Gtk::ComboBoxText *combo);

    void closeSettingsWindow();

    void setActiveElementFromConfigFile(Gtk::ComboBoxText *sizeDisplayFormatCombo) const;
};
#endif /** SETTINGS_WINDOW_H **/
