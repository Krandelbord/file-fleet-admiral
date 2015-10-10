#include "SettingsWindow.h"
#include "config.h"

SettingsWindow::SettingsWindow(Gtk::Window& parent) : Gtk::Dialog(_("Settings Window"), parent) {
    Gtk::HBox *labelValueBox = Gtk::manage(new Gtk::HBox());

    Gtk::Label *sizeDisplayFormatLabel = Gtk::manage(new Gtk::Label(_("File size display format: ")));
    labelValueBox->add(*sizeDisplayFormatLabel);
    Gtk::ComboBoxText *sizeDisplayFormatCombo = Gtk::manage(new Gtk::ComboBoxText());
    sizeDisplayFormatCombo->append(_("In bytes (for example 12345)"));
    sizeDisplayFormatCombo->append(_("Space separated (for example 12 345)"));
    sizeDisplayFormatCombo->append(_("Human readable simple (for example 12kB)"));
    sizeDisplayFormatCombo->append(_("Human readable full (for example 12kB 57B)"));
    labelValueBox->add(*sizeDisplayFormatCombo);

    this->get_vbox()->add(*labelValueBox);
    this->show_all();
}
