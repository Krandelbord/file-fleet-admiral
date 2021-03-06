#ifndef FILE_FLEET_ADMIRAL_RENAMEPOPUP_H
#define FILE_FLEET_ADMIRAL_RENAMEPOPUP_H


#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm.h>
#include "../operations/RenameExecutor.h"
#include "../operations/NotifiableByContentChange.h"

class RenamePopup : public Gtk::Dialog {
public:
    RenamePopup(Gtk::Window &parent, NotifiableByContentChange *notifiableContentChange, const Glib::RefPtr<Gio::File> &originalFile);
    ~RenamePopup() override;
private:
    Gtk::Entry newFileNameTextEntry;
    Gtk::ProgressBar progressBar;
    Gtk::Button *renameBtn;
    Gtk::Button *cancelBtn;
    RenameExecutor renameExecutor;
    Gtk::Grid gridContainer;
    NotifiableByContentChange *notifiableContentChange;

    std::shared_ptr<InterThreadProgressPipe> threadMsgs;
    void onCancel();
    void executeRename(Glib::RefPtr<Gio::File> &originalFile);
    void onRenameDone(const Glib::RefPtr<Gio::File> &originalFilePath);
    void onRenameProgressing(const std::shared_ptr<InterThreadProgressPipe>& threadMessage);
    void onFailureFromRename();

    void startRenamingThread(Glib::RefPtr<Gio::File>& originalFilePath);

    bool onWindowClose(GdkEventAny* gdkEvent);

    Gtk::Label *addLabel(const Glib::ustring &str, int left, int top);

    void addIcon(int left, int top);
};


#endif //FILE_FLEET_ADMIRAL_RENAMEPOPUP_H
