/**
 * Test of muli thread dirs reading
 */
#include <vector>
#include <functional>
#include <memory>
#include "Runner.h"
#include "../ThreadMessage.h"
#include "../GuiReader.h"


bool doNewWork() {
    Glib::ustring testedDirectory = "/var/lib/";
    GuiReader guiReader;
    std::vector<FileListElement> dirContent = guiReader.executeCommandAndWaitForData(std::make_shared<ThreadMessage>(testedDirectory));

    for (auto oneDirElement : dirContent) {
        //thoused of times we change mind which directoy we will read
        Glib::ustring newDirToRead = testedDirectory + oneDirElement.getFileName();
        std::shared_ptr<ThreadMessage> threadMsng = std::make_shared<ThreadMessage>(newDirToRead);        
        guiReader.commandReadThis(threadMsng);
    }
    guiReader.waitForFinishWork();

    //it is success if it didn't crashed
    return true;
}

int main() {
    std::vector<std::function<bool()>> testsToRun;
    testsToRun.push_back(doNewWork);

    Runner runner;
    for (auto oneTestToRun : testsToRun) {
        runner.run(oneTestToRun);
    }

    runner.showStats();
}


