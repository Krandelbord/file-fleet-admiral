#ifndef FILE_FLEET_ADMIRAL_RENAMEPOPUP_H
#define FILE_FLEET_ADMIRAL_RENAMEPOPUP_H


#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include "../operations/RenameExecutor.h"

class RenamePopup : public Gtk::Dialog {
public:
    RenamePopup(Gtk::Window &parent, const Glib::RefPtr<Gio::File> &originalFile);
    ~RenamePopup() override;
private:
    Gtk::Label label;
    Gtk::Entry newFileNameTextEntry;
    Gtk::ProgressBar progressBar;
    Gtk::Button *renameBtn;
    Gtk::Button *cancelBtn;
    RenameExecutor renameExecutor;


    std::shared_ptr<InterThreadProgressPipe> threadMsgs;
    void onCancel();
    void executeRename(Glib::RefPtr<Gio::File> &originalFile);
    void onRenameDone();
    void onRenameProgressing(const std::shared_ptr<InterThreadProgressPipe>& threadMessage);
    void onFailureFromRename();

    void startRenamingThread(Glib::RefPtr<Gio::File>& originalFilePath);

    bool onWindowClose(GdkEventAny* gdkEvent);
};


#endif //FILE_FLEET_ADMIRAL_RENAMEPOPUP_H
