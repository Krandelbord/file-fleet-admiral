#include "SettingsWindow.h"
#include "SizeDisplayFormat.h"
#include "config.h"

SettingsWindow::SettingsWindow(Gtk::Window& parent) : Gtk::Dialog(_("Settings Window"), parent) {
    Gtk::HBox *labelValueBox = Gtk::manage(new Gtk::HBox());

    Gtk::Label *sizeDisplayFormatLabel = Gtk::manage(new Gtk::Label(_("File size display format: ")));
    labelValueBox->add(*sizeDisplayFormatLabel);
    Gtk::ComboBoxText *sizeDisplayFormatCombo = Gtk::manage(new Gtk::ComboBoxText());
    sizeDisplayFormatCombo->append(convertSizeDFToString(SizeDisplayFormat::IN_BYTES), _("In bytes (for example 12345)"));
    sizeDisplayFormatCombo->append(convertSizeDFToString(SizeDisplayFormat::SPACE_SEPARATED), _("Space separated (for example 12 345)"));
    sizeDisplayFormatCombo->append(convertSizeDFToString(SizeDisplayFormat::HR_ROUNDED), _("Human readable simple (for example 12kB)"));
    sizeDisplayFormatCombo->append(convertSizeDFToString(SizeDisplayFormat::HR_FULL), _("Human readable full (for example 12kB 57B)"));
    sizeDisplayFormatCombo->set_active(0);
    labelValueBox->add(*sizeDisplayFormatCombo);

    this->get_vbox()->add(*labelValueBox);
    addImageButton("cancel", _("Cancel"));
    addImageButton("document-save", _("Save settings"));
    this->show_all();
}

Gtk::Button* SettingsWindow::addImageButton(const Glib::ustring &iconName, const Glib::ustring& label) {
    Gtk::Button* buttonBeingAdded = Gtk::manage(new Gtk::Button(label, true));
    Gtk::Image* icon = Gtk::manage(new Gtk::Image());
    icon->set_from_icon_name(iconName, Gtk::BuiltinIconSize::ICON_SIZE_BUTTON);

    //buttonBeingAdded->set_image(*icon);
    buttonBeingAdded->set_label(label);
    this->get_action_area()->add(*buttonBeingAdded);
    return buttonBeingAdded;
}