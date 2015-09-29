/**
 * Test of muli thread dirs reading
 */
#include <vector>
#include <functional>
#include <memory>
#include "Runner.h"
#include "../FilesReadWorker.h"

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

int main() {
    std::vector<std::function<bool()>> testsToRun;
    testsToRun.push_back(shouldReadMultiDirsInMultiThread);
    Runner runner;
    for (auto oneTestToRun : testsToRun) {
        runner.run(oneTestToRun);
    }

    runner.showStats();
}


