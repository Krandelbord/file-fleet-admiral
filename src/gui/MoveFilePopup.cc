#include <gtkmm/progressbar.h>
#include "MoveFilePopup.h"
#include "MainWindow.h"
#include "../config.h"
#include "../operations/ThreadPerformingMove.h"

MoveFilePopup::MoveFilePopup(Gtk::Window &parent,
                         NotifiableByContentChange *notifiableContentChange,
                             const Glib::RefPtr<Gio::File>& fileToMove,
                             const Glib::ustring& destinationDir) :
        Gtk::Dialog(_("Move file"), parent) {
    this->set_default_size(100, 100);
    this->set_modal(false);
    this->get_action_area()->set_layout(Gtk::ButtonBoxStyle::BUTTONBOX_CENTER);
    this->notifiableContentChange = notifiableContentChange;
    label.set_label("Move file from „" + fileToMove->get_path() + "”");
    label.set_justify(Gtk::JUSTIFY_LEFT);
    label.set_halign(Gtk::ALIGN_START);
    this->get_content_area()->pack_start(label, Gtk::PackOptions::PACK_SHRINK);

    destinationPathEntry.set_text(destinationDir);
    destinationPathEntry.set_activates_default(true);
    this->get_content_area()->pack_start(destinationPathEntry, Gtk::PackOptions::PACK_SHRINK);

    cancelBtn = this->add_button("gtk-cancel", Gtk::RESPONSE_CANCEL);
    cancelBtn->set_always_show_image(true);

    renameBtn = this->add_button(_("Move"), Gtk::RESPONSE_OK);
    renameBtn->set_always_show_image(true);
    renameBtn->set_image_from_icon_name("gtk-apply");
    this->set_default(*renameBtn);
    cancelBtn->signal_clicked().connect(sigc::mem_fun(*this, &MoveFilePopup::onCancel));
    renameBtn->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &MoveFilePopup::executeMove), fileToMove));
    this->signal_delete_event().connect(sigc::mem_fun(*this, &MoveFilePopup::onWindowClose));
    this->show_all_children();
}

MoveFilePopup::~MoveFilePopup() {
    gfm_debug("Destructor of move popup\n");
}

void MoveFilePopup::onCancel() {
    if (threadMsgs->isWorkEnded()) {
        //trick to notify that nothing was changed
        onMoveDone(Gio::File::create_for_path("/"));
    } else {
        threadMsgs->cancelWork();
    }
}

void MoveFilePopup::onMoveProgressing(const std::shared_ptr<InterThreadProgressPipe> &threadMessage) {
    float progress = threadMessage->getCurrentProgress();
    gfm_debug("It is moving forward %f\n", progress);
    this->progressBar.set_fraction(progress);
    this->progressBar.set_text(Glib::ustring::compose<>("%1%% done", (int) (progress * 100)));
}

void MoveFilePopup::onFailureFromMove() {
    if (!threadMsgs->isSuccess()) {
        Gtk::Label* errorMessageLabel = Gtk::manage(new Gtk::Label(threadMsgs->getMessage()));
        errorMessageLabel->set_padding(DEFAULT_LABEL_PADDING, DEFAULT_LABEL_PADDING);
        this->get_content_area()->pack_start(*errorMessageLabel, Gtk::PackOptions::PACK_EXPAND_WIDGET);
        errorMessageLabel->show_all();
        this->progressBar.hide();
    }
}

void MoveFilePopup::onMoveDone(const Glib::RefPtr<Gio::File> &originalFilePath) {
    gfm_debug("Rename is done\n");
    if (threadMsgs->isSuccess()) {
        notifiableContentChange->notifyRefreshDirs(originalFilePath->get_parent());
    }
    delete this;
}

void MoveFilePopup::executeMove(Glib::RefPtr<Gio::File> &originalFile) {
    gfm_debug("Executing move to „%s”\n", this->destinationPathEntry.get_text().c_str());
    this->get_content_area()->pack_start(progressBar, Gtk::PackOptions::PACK_EXPAND_WIDGET, 5);
    this->get_content_area()->remove(destinationPathEntry);
    progressBar.set_text("Fraction done");
    progressBar.set_show_text(true);
    progressBar.set_halign(Gtk::ALIGN_CENTER);
    progressBar.set_valign(Gtk::ALIGN_CENTER);
    progressBar.set_vexpand(true);
    progressBar.set_vexpand_set(true);
    progressBar.show_all();
    destinationPathEntry.hide();
    renameBtn->set_sensitive(false);
    renameBtn->set_tooltip_text(_("Move operation is already stared"));
    startMoveFileThread(originalFile);
}

void MoveFilePopup::startMoveFileThread(Glib::RefPtr<Gio::File> &originalFilePath) {
    threadMsgs = std::make_shared<InterThreadProgressPipe>();
    // Connect the handler to the dispatcher.
    threadMsgs->connectWorkFinishedSignal(sigc::bind(sigc::mem_fun(*this, &MoveFilePopup::onMoveDone), originalFilePath));
    threadMsgs->connectProgressUpdate(sigc::bind(sigc::mem_fun(*this, &MoveFilePopup::onMoveProgressing), threadMsgs));
    threadMsgs->connectWorkFailedSignal(sigc::mem_fun(*this, &MoveFilePopup::onFailureFromMove));

    ThreadPerformingMove threadObj;
    Glib::Threads::Thread::create(
            sigc::bind(sigc::mem_fun(threadObj, &ThreadPerformingMove::threadFunction),
                       threadMsgs,
                       originalFilePath,
                       destinationPathEntry.get_text()));

}


bool MoveFilePopup::onWindowClose(GdkEventAny *gdkEvent) {
    gfm_debug("On window close\n");
    if (threadMsgs) {
        threadMsgs->cancelWork();
    }
    return false;
}
