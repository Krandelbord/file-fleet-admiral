/**
 * Test of muli thread dirs reading
 */
#include <vector>
#include <functional>
#include "Runner.h"

bool shouldReadMultiDirsInMultiThread() {
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