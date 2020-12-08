#include "RenamePopup.h"
#include "../config.h"

RenamePopup::RenamePopup(Gtk::Window &parent, Glib::ustring &renamePath) : Gtk::Dialog(_("Rename Window"), parent) {
    this->set_default_size(100, 100);
    label.set_label(renamePath);
    label.set_justify(Gtk::JUSTIFY_LEFT);
    this->set_modal(false);
    this->get_vbox()->pack_start(label, Gtk::PackOptions::PACK_SHRINK);
    this->get_vbox()->pack_start(newFileName, Gtk::PackOptions::PACK_SHRINK);

    Gtk::Button *cancelBtn = this->add_button("gtk-cancel", Gtk::RESPONSE_CANCEL);
    cancelBtn->set_always_show_image(true);

    Gtk::Button *renameBtn = this->add_button(_("Rename"), Gtk::RESPONSE_OK);
    renameBtn->set_always_show_image(true);
    renameBtn->set_image_from_icon_name("gtk-apply");

    cancelBtn->signal_clicked().connect(sigc::mem_fun(*this, &RenamePopup::onCancel));
    renameBtn->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &RenamePopup::executeRename), newFileName.get_text()));
    this->show_all_children();
}

RenamePopup::~RenamePopup() {
    gfm_debug("Destructor of rename popup\n");
}

void RenamePopup::onCancel() {
    delete this;
}

void RenamePopup::executeRename(Glib::ustring newFileName) {
    gfm_debug("Executing rename to „%s”\n", this->newFileName.get_text().c_str());
}