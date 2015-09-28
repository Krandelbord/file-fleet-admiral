/**
 * Test of muli thread dirs reading
 */
#include <vector>
#include <functional>
#include "Runner.h"
#include "../FilesReadWorker.h"

class NotiferForTests : public WorkerNotifable {
    void notifyNewDataFromThread() {
        gfm_debug("Nothing \n");
    }
};

bool shouldReadMultiDirsInMultiThread() {
    WorkerNotifable *notifer = new NotiferForTests();
    for (int i=0; i<1000; ++i) {
        gfm_debug("Iteracja nr %d\n", i);
        FilesReadWorker worker("/home/emil", FilesSortType::UNSORTED, notifer);
    }
    return false;
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


