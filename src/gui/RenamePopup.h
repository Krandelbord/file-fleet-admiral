#ifndef FILE_FLEET_ADMIRAL_RENAMEPOPUP_H
#define FILE_FLEET_ADMIRAL_RENAMEPOPUP_H


#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>

class RenamePopup : public Gtk::Dialog {
public:
    RenamePopup(Gtk::Window &parent, Glib::ustring &renamePath);
    ~RenamePopup() override;
private:
    Gtk::Label label;
    Gtk::Entry newFileName;

    void onCancel();
    void executeRename(Glib::ustring newFileName);
};


#endif //FILE_FLEET_ADMIRAL_RENAMEPOPUP_H
