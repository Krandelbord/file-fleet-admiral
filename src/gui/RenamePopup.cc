#include <gtkmm/progressbar.h>

#include "RenamePopup.h"
#include "../config.h"
#include "MainWindow.h"

RenamePopup::RenamePopup(Gtk::Window &parent,
                         NotifiableByContentChange *notifiableContentChange,
                         const Glib::RefPtr<Gio::File> &originalFile) :
        Gtk::Dialog(_("Rename"), parent) {
    this->set_default_size(100, 100);
    this->set_modal(false);

    this->get_action_area()->set_layout(Gtk::ButtonBoxStyle::BUTTONBOX_CENTER);
    this->get_action_area()->set_margin_top(DEFAULT_LABEL_PADDING);
    this->get_action_area()->set_margin_bottom(DEFAULT_LABEL_PADDING);

    this->notifiableContentChange = notifiableContentChange;
    int positionLeft = 0;
    int positionTop = 0;
    addIcon(positionLeft++, positionTop);
    addLabel(_("Rename:"), positionLeft++, positionTop);
    addLabel(Glib::ustring::compose<>("„%1”", originalFile->get_basename()), positionLeft, positionTop++);

    newFileNameTextEntry.set_text(originalFile->get_basename());
    newFileNameTextEntry.set_activates_default(true);
    this->get_content_area()->pack_start(gridContainer);
    gridContainer.set_margin_bottom(DEFAULT_LABEL_PADDING);
    gridContainer.set_column_spacing(DEFAULT_LABEL_PADDING);
    gridContainer.set_margin_right(DEFAULT_POPUP_MARGIN);
    gridContainer.set_margin_left(DEFAULT_POPUP_MARGIN);
    positionLeft=1;
    addLabel(_("New name:"), positionLeft++, positionTop);
    gridContainer.attach(newFileNameTextEntry, positionLeft++, positionTop);

    cancelBtn = this->add_button("gtk-cancel", Gtk::RESPONSE_CANCEL);
    cancelBtn->set_margin_start(DEFAULT_POPUP_MARGIN);
    cancelBtn->set_margin_end(DEFAULT_POPUP_MARGIN);

    cancelBtn->set_always_show_image(true);

    renameBtn = this->add_button(_("Rename"), Gtk::RESPONSE_OK);
    renameBtn->set_margin_start(DEFAULT_POPUP_MARGIN);
    renameBtn->set_margin_end(DEFAULT_POPUP_MARGIN);
    renameBtn->set_always_show_image(true);
    renameBtn->set_image_from_icon_name("gtk-apply");
    this->set_default(*renameBtn);
    cancelBtn->signal_clicked().connect(sigc::mem_fun(*this, &RenamePopup::onCancel));
    renameBtn->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &RenamePopup::executeRename), originalFile));
    this->signal_delete_event().connect(sigc::mem_fun(*this, &RenamePopup::onWindowClose));
    this->show_all_children();
}

Gtk::Label * RenamePopup::addLabel(const Glib::ustring &str, int left, int top) {
    Gtk::Label *label = Gtk::manage(new Gtk::Label(str));
    label->set_label(str);
    label->set_justify(Gtk::JUSTIFY_LEFT);
    label->set_halign(Gtk::ALIGN_START);
    label->set_padding(DEFAULT_LABEL_PADDING, DEFAULT_LABEL_PADDING);
    gridContainer.attach(*label, left, top);
    label->show_all();
    return label;
}

RenamePopup::~RenamePopup() {
    gfm_debug("Destructor of rename popup\n");
}

void RenamePopup::onCancel() {
    if (threadMsgs && threadMsgs->isWorkEnded()) {
        //trick to notify that nothing was changed
        onRenameDone(Gio::File::create_for_path("/"));
    } else if (threadMsgs) {
        threadMsgs->cancelWork();
    } else {
        //operation wasn't even started. Just close popup
        delete this;
    }
}

void RenamePopup::onRenameProgressing(const std::shared_ptr<InterThreadProgressPipe> &threadMessage) {
    float progress = threadMessage->getCurrentProgress();
    gfm_debug("It is moving forward %f\n", progress);
    this->progressBar.set_fraction(progress);
    this->progressBar.set_text(Glib::ustring::compose<>("%1%% done", (int) (progress * 100)));
}

void RenamePopup::onFailureFromRename() {
    if (!threadMsgs->isSuccess()) {
        Gtk::Label *errorMessageLabel = Gtk::manage(new Gtk::Label(threadMsgs->getMessage()));
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
    this->get_content_area()->remove(newFileNameTextEntry);
    addLabel(Glib::ustring::compose<>("„%1”", newFileNameTextEntry.get_text()), 2, 1);
    this->gridContainer.attach(progressBar, 0, 3, 3, 1);
    progressBar.set_text("Fraction done");
    progressBar.set_show_text(true);
    progressBar.show_all();
    newFileNameTextEntry.hide();
    renameBtn->set_sensitive(false);
    renameBtn->set_tooltip_text(_("Rename operation is already stared"));
    startRenamingThread(originalFile);
}

void RenamePopup::startRenamingThread(Glib::RefPtr<Gio::File> &originalFilePath) {
    threadMsgs = std::make_shared<InterThreadProgressPipe>();
    // Connect the handler to the dispatcher.
    threadMsgs->connectWorkFinishedSignal(
            sigc::bind(sigc::mem_fun(*this, &RenamePopup::onRenameDone), originalFilePath));
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

void RenamePopup::addIcon(int left, int top) {
    Gtk::Image *renameIcon = new Gtk::Image("gtk-save-as", Gtk::ICON_SIZE_DIALOG);
    gridContainer.attach(*renameIcon, left, top, 1, 2);
}
