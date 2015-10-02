/**
 * Test of muli thread dirs reading
 */
#include <vector>
#include <functional>
#include <memory>
#include "Runner.h"
#include "../FilesReadWorker.h"
#include "../ThreadMessage.h"
#include "../GuiReader.h"

class NotiferForTests : public WorkerNotifable {
    void notifyNewDataFromThread() {
        gfm_debug("Nothing \n");
    }
};

bool shouldReadMultiDirsInMultiThread() {
    std::shared_ptr<WorkerNotifable> notifer = std::make_shared<NotiferForTests>();
    for (int i=0; i<1000; ++i) {
        gfm_debug("Iteracja nr %d\n", i);
        FilesReadWorker worker("/usr/share/doc", FilesSortType::UNSORTED, notifer.get());
    }
    return true;
}

bool doNewWork() {
    GuiReader guiReader;
    std::vector<FileListElement> dirContent = guiReader.executeCommandAndWaitForData(std::make_shared<ThreadMessage>("/usr/share/doc"));

    for (auto oneDirElement : dirContent) {
        gfm_debug("once again \n");
        //thoused of times we change mind which directoy we will read
        std::shared_ptr<ThreadMessage> threadMsng = std::make_shared<ThreadMessage>(oneDirElement.getFileName());        
        guiReader.commandReadThis(threadMsng);
    }
    guiReader.waitForFinishWork();
    return true;
}

int main() {
    std::vector<std::function<bool()>> testsToRun;
    //testsToRun.push_back(shouldReadMultiDirsInMultiThread);
    testsToRun.push_back(doNewWork);

    Runner runner;
    for (auto oneTestToRun : testsToRun) {
        runner.run(oneTestToRun);
    }

    runner.showStats();
}


