#include <cstddef>
#include <string>
#include "Asserts.h"
#include "Runner.h"

bool checkSizeFormatting(size_t sizeToFormatInBytes, const std::string expectedOut) {
    return true;
}

int main() {
    std::vector<std::function<bool()>> testsToRun;
    testsToRun.push_back(std::bind(checkSizeFormatting, 12345, "12 345"));

    Runner runner;
    for (auto oneTestToRun : testsToRun) {
        runner.run(oneTestToRun);
    }

    runner.showStats();
}