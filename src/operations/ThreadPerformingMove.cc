#include "ThreadPerformingMove.h"
#include "../config.h"
#include "../gui/SizeFormatterHr.h"

#define SECONDS_IN_MICROSECOND 10e-6

void ThreadPerformingMove::threadFunction(std::shared_ptr<InterThreadProgressPipe> threadMessage,
                                          Glib::RefPtr<Gio::File> &originalFile,
                                          const Glib::ustring &destinationDirPath) {
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
    const Glib::RefPtr<Gio::File> &destinationFile = Gio::File::create_for_path(
            Glib::build_filename(destinationDir->get_path(), originalFile->get_basename()));
    gfm_debug("Moving „%s” to „%s”\n", originalFile->get_path().c_str(), destinationFile->get_path().c_str());
    Glib::DateTime operationStart = Glib::DateTime::create_now_local();
    try {
        originalFile->move(destinationFile,
                           sigc::bind(sigc::mem_fun(*this, &ThreadPerformingMove::onMoveProgressing), operationStart,
                                      threadMessage),
                           threadMessage->getCancellable());
    } catch (const Glib::Error &exc) {
        gfm_debug("Error code is %d\n", exc.code());
        gfm_debug("Class is %s\n", typeid(exc).name());
        threadMessage->setMessage("Oja: " + exc.what());
        threadMessage->notifyWorkFailed();
        return;
    }
    gfm_debug("This is the end of move\n");
}

void ThreadPerformingMove::onMoveProgressing(goffset current, goffset total,
                                             Glib::DateTime startTime,
                                             std::shared_ptr<InterThreadProgressPipe> threadMessage) {
    gfm_debug("Read %ld of %ld\n", current, total);
    double progressAsFraction = (1.0 * current) / (1.0 * total);
    gfm_debug("Progress is %f\n", progressAsFraction);
    long durationInUs = Glib::DateTime::create_now_local().difference(startTime);
    gfm_debug("Current duration is %ld\n", durationInUs);
    SizeFormatterHr formatterHr;
    const std::string &speedPerSecond = formatterHr.formatSize(
            current / (static_cast<double>(durationInUs) * SECONDS_IN_MICROSECOND));
    gfm_debug("Current speed %s/s\n", speedPerSecond.c_str());
    threadMessage->updateProgress(static_cast<float>(progressAsFraction));
    if (current == total) {
        threadMessage->notifyWorkEnded();
    }
}