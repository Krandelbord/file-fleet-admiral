//
// Created by enowak on 28.09.15.
//

#include "Runner.h"
#include <iostream>

#define COLOR_RESET "\x1b[0m"
#define COLOR_RED   "\x1b[31;1m"
#define COLOR_GREEN "\x1b[32;1m"


void Runner::showStats() {
    if (totalCount == successCount) {
        std::cout << COLOR_GREEN;
    } else {
        std::cout << COLOR_RED;
    }
    std::cout << "Tests finished. Success " << successCount << " of " << totalCount << COLOR_RESET << std::endl ;
}

void Runner::run(std::function<bool()> oneTestFunction) {
    doRun(oneTestFunction());
}

void Runner::doRun(bool runResultWasSuccess) {
    totalCount++;
    if (runResultWasSuccess) {
        successCount++;
    }
}