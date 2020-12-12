#include <gtkmm/progressbar.h>

#include "RenamePopup.h"
#include "../config.h"
#include "MainWindow.h"
#include "../operations/NotifiableByContentChange.h"

RenamePopup::RenamePopup(Gtk::Window &parent,
                         NotifiableByContentChange *notifiableContentChange,
                         const Glib::RefPtr<Gio::File> &originalFile) :
                         Gtk::Dialog(_("Rename Window"), parent) {
    this->set_default_size(100, 100);
    this->set_modal(false);
    this->get_action_area()->set_layout(Gtk::ButtonBoxStyle::BUTTONBOX_CENTER);
    this->notifiableContentChange = notifiableContentChange;
    label.set_label("Rename „" + originalFile->get_basename() + "”");
    label.set_justify(Gtk::JUSTIFY_LEFT);
    label.set_halign(Gtk::ALIGN_START);
    this->get_content_area()->pack_start(label, Gtk::PackOptions::PACK_SHRINK);

    newFileNameTextEntry.set_text(originalFile->get_basename());
    newFileNameTextEntry.set_activates_default(true);
    this->get_content_area()->pack_start(newFileNameTextEntry, Gtk::PackOptions::PACK_SHRINK);

    cancelBtn = this->add_button("gtk-cancel", Gtk::RESPONSE_CANCEL);
    cancelBtn->set_always_show_image(true);

    renameBtn = this->add_button(_("Rename"), Gtk::RESPONSE_OK);
    renameBtn->set_always_show_image(true);
    renameBtn->set_image_from_icon_name("gtk-apply");
    this->set_default(*renameBtn);
    cancelBtn->signal_clicked().connect(sigc::mem_fun(*this, &RenamePopup::onCancel));
    renameBtn->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &RenamePopup::executeRename), originalFile));
    this->signal_delete_event().connect(sigc::mem_fun(*this, &RenamePopup::onWindowClose));
    this->show_all_children();
}

RenamePopup::~RenamePopup() {
    gfm_debug("Destructor of rename popup\n");
}

void RenamePopup::onCancel() {
    if (threadMsgs->isWorkEnded()) {
        //trick to notify that nothing was changed
        onRenameDone(Gio::File::create_for_path("/"));
    } else {
        threadMsgs->cancelWork();
    }
}

void RenamePopup::onRenameProgressing(const std::shared_ptr<InterThreadProgressPipe> &threadMessage) {
    float progress = threadMessage->getCurrentProgress();
    gfm_debug("It is moving forward %f\n", progress);
    this->progressBar.set_fraction(progress);
    this->progressBar.set_text(Glib::ustring::compose<>("%1%% done", (int) (progress * 10)));
}

void RenamePopup::onFailureFromRename() {
    if (!threadMsgs->isSuccess()) {
        Gtk::Label* errorMessageLabel = Gtk::manage(new Gtk::Label(threadMsgs->getMessage()));
        errorMessageLabel->set_padding(DEFAULT_LABEL_PADDING, DEFAULT_LABEL_PADDING);
        this->get_content_area()->pack_start(*errorMessageLabel, Gtk::PackOptions::PACK_EXPAND_WIDGET);
        errorMessageLabel->show_all();
        this->progressBar.hide();
    }
}

void RenamePopup::onRenameDone(const Glib::RefPtr<Gio::File> &originalFilePath) {
    gfm_debug("Rename is done\n");
    if (threadMsgs->isSuccess()) {
        notifiableContentChange->notifyRefreshDirs(originalFilePath->get_parent());
    }
    delete this;
}

void RenamePopup::executeRename(Glib::RefPtr<Gio::File> &originalFile) {
    gfm_debug("Executing rename to „%s”\n", this->newFileNameTextEntry.get_text().c_str());
    this->get_content_area()->pack_start(progressBar, Gtk::PackOptions::PACK_EXPAND_WIDGET, 5);
    this->get_content_area()->remove(newFileNameTextEntry);
    progressBar.set_text("Fraction done");
    progressBar.set_show_text(true);
    progressBar.set_halign(Gtk::ALIGN_CENTER);
    progressBar.set_valign(Gtk::ALIGN_CENTER);
    progressBar.set_vexpand(true);
    progressBar.set_vexpand_set(true);
    progressBar.show_all();
    newFileNameTextEntry.hide();
    renameBtn->set_sensitive(false);
    renameBtn->set_tooltip_text(_("Rename operation is already stared"));
    startRenamingThread(originalFile);
}

void RenamePopup::startRenamingThread(Glib::RefPtr<Gio::File> &originalFilePath) {
    threadMsgs = std::make_shared<InterThreadProgressPipe>();
    // Connect the handler to the dispatcher.
    threadMsgs->connectWorkFinishedSignal(sigc::bind(sigc::mem_fun(*this, &RenamePopup::onRenameDone), originalFilePath));
    threadMsgs->connectProgressUpdate(sigc::bind(sigc::mem_fun(*this, &RenamePopup::onRenameProgressing), threadMsgs));
    threadMsgs->connectWorkFailedSignal(sigc::mem_fun(*this, &RenamePopup::onFailureFromRename));
    renameExecutor.executeRename(threadMsgs, originalFilePath, newFileNameTextEntry.get_text());
}


bool RenamePopup::onWindowClose(GdkEventAny *gdkEvent) {
    gfm_debug("On window close\n");
    if (threadMsgs) {
        threadMsgs->cancelWork();
    }
    return false;
}
