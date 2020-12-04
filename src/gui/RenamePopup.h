#ifndef FILE_FLEET_ADMIRAL_RENAMEPOPUP_H
#define FILE_FLEET_ADMIRAL_RENAMEPOPUP_H


#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>

class RenamePopup : public Gtk::Dialog {
public:
    RenamePopup(Gtk::Window &parent, Glib::ustring &renamePath);
private:
    Gtk::Label label;
    Gtk::Entry newFileName;
};


#endif //FILE_FLEET_ADMIRAL_RENAMEPOPUP_H
