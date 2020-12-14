#ifndef FILE_FLEET_ADMIRAL_MOVEFILEPOPUP_H
#define FILE_FLEET_ADMIRAL_MOVEFILEPOPUP_H

#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm.h>
#include "../operations/RenameExecutor.h"
#include "../operations/NotifiableByContentChange.h"


class MoveFilePopup : public Gtk::Dialog {
public:
    MoveFilePopup(Gtk::Window &parent, NotifiableByContentChange *notifiableContentChange,
                  const Glib::RefPtr<Gio::File>& fileToMove,
                  const Glib::ustring& destinationDir);
    ~MoveFilePopup() override;
private:
    Gtk::Label label;
    Gtk::Entry destinationPathEntry;
    Gtk::ProgressBar progressBar;
    Gtk::Button *renameBtn;
    Gtk::Button *cancelBtn;
    RenameExecutor renameExecutor;
    NotifiableByContentChange *notifiableContentChange;

    std::shared_ptr<InterThreadProgressPipe> threadMsgs;
    void onCancel();
    void executeMove(Glib::RefPtr<Gio::File> &originalFile);
    void onMoveDone(const Glib::RefPtr<Gio::File> &originalFilePath);
    void onMoveProgressing(const std::shared_ptr<InterThreadProgressPipe>& threadMessage);
    void onFailureFromMove();

    void startMoveFileThread(Glib::RefPtr<Gio::File>& originalFilePath);

    bool onWindowClose(GdkEventAny* gdkEvent);
};


#endif //FILE_FLEET_ADMIRAL_MOVEFILEPOPUP_H
