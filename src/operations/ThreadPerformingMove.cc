#include "ThreadPerformingMove.h"
#include "../config.h"

void ThreadPerformingMove::threadFunction(std::shared_ptr<InterThreadProgressPipe> threadMessage,
                                            Glib::RefPtr<Gio::File> &originalFile,
                                            const Glib::ustring& destinationDirPath) {
    threadMessage->updateProgress(0.1);
    bool sourceFileExists = originalFile->query_exists(threadMessage->getCancellable());
    const Glib::RefPtr<Gio::File> &destinationDir = Gio::File::create_for_path(destinationDirPath);

    const Glib::RefPtr<Gio::FileInfo> &destinationInfo = destinationDir->query_info();

    if (!Glib::file_test(destinationDirPath, Glib::FileTest::FILE_TEST_IS_DIR)) {
        threadMessage->updateProgress(1);
        threadMessage->setMessage(_("Destination is not directory"));
        threadMessage->notifyWorkFailed();
        return;
    }
    if (!destinationDir->query_exists(threadMessage->getCancellable())) {
        threadMessage->updateProgress(1);
        threadMessage->setMessage(_("Destination doesn't exists"));
        threadMessage->notifyWorkFailed();
        return;
    }
    if (!sourceFileExists) {
        threadMessage->updateProgress(1);
        threadMessage->setMessage(_("Source file doesn't exists"));
        threadMessage->notifyWorkFailed();
        return;
    }
    const Glib::RefPtr<Gio::File>& destinationFile = Gio::File::create_for_path(Glib::build_filename(destinationDir->get_path(), originalFile->get_basename()));
    gfm_debug("Moving „%s” to „%s”\n", originalFile->get_path().c_str(), destinationFile->get_path().c_str());
    this->operationStart = Glib::DateTime::create_now_local();
    try {
        originalFile->move(destinationFile,
                           sigc::bind(sigc::mem_fun(*this, &ThreadPerformingMove::onMoveProgressing), threadMessage),
                           threadMessage->getCancellable());
    } catch (const Glib::Error& exc) {
        threadMessage->setMessage(exc.what());
        threadMessage->notifyWorkFailed();
        return;
    }
}

void ThreadPerformingMove::onMoveProgressing(goffset current, goffset total, std::shared_ptr<InterThreadProgressPipe> threadMessage) {
    gfm_debug("Read %ld of %ld\n", current, total);
    double progressAsFraction = (1.0*current) / (1.0*total);
    gfm_debug("Progress is %f\n", progressAsFraction);
    threadMessage->updateProgress(progressAsFraction);
    if (current==total) {
        threadMessage->notifyWorkEnded();
    }
}