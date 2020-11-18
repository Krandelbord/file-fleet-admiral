#include <iostream>
#include "Asserts.h"
#include "../src/gui/PathResolver.h"
#include "../src/gui/SelectionHistory.h"
#include "Runner.h"

/**
 * Returns true for cussess 
 */
bool checkDirGeneration(const Glib::ustring& startDir, const Glib::ustring& cdCommand, const Glib::ustring expected) {
    PathResolver path(startDir);
    path.changeDirBy(cdCommand);

    return Asserts::assertEquals("Values not equal", expected, path.toString());
}

bool shouldPersist3LevelSelection() {
    SelectionHistory selHistory("/home/emil/music");
    selHistory.changeDirBy("Judas Priest");
    selHistory.changeDirBy("1993 - Metal Works");
    selHistory.changeDirBy("CD2");

    return Asserts::assertEquals("Values not equal", "Judas Priest", selHistory.getSelectionForDir("/home/emil/music"));
}

bool shouldPersistDirUpSelection() {
    SelectionHistory selHistory("/home/emil/music");
    selHistory.changeDirBy("Judas Priest");
    selHistory.changeDirBy("1993 - Metal Works");
    selHistory.changeDirBy("..");

    return Asserts::assertEquals("Values not equal", "1993 - Metal Works", selHistory.getSelectionForDir("/home/emil/music/Judas Priest"));
}

bool shouldPersistSelection() {
    SelectionHistory selHistory("/home/emil/Documents");
    selHistory.changeDirBy("drawings");

    return Asserts::assertEquals("Values not equal", "drawings", selHistory.getSelectionForDir("/home/emil/Documents"));
}

bool shouldPersistGoingBackToSomeRoot() { 
    SelectionHistory selHistory("/home/emil/music");
    selHistory.changeDirBy("Judas Priest");
    selHistory.changeDirBy("..");
    selHistory.changeDirBy("Iron Maiden");
    selHistory.changeDirBy("..");

    return Asserts::assertEquals("Values not equal", "Iron Maiden", selHistory.getSelectionForDir("/home/emil/music"));
}

int main() {
    std::vector<std::function<bool()>> testsToRun;
    testsToRun.push_back(std::bind(checkDirGeneration, "/home/emil/Documents", "notes", "/home/emil/Documents/notes"));
    testsToRun.push_back(std::bind(checkDirGeneration, "/home/emil/Documents", "..", "/home/emil"));
    testsToRun.push_back(std::bind(checkDirGeneration, "/", "..", "/"));
    testsToRun.push_back(std::bind(checkDirGeneration, "/home", "..", "/"));
    testsToRun.push_back(std::bind(checkDirGeneration, "/", "home", "/home"));
    testsToRun.push_back(shouldPersistSelection);
    testsToRun.push_back(shouldPersist3LevelSelection);
    testsToRun.push_back(shouldPersistDirUpSelection);
    testsToRun.push_back(shouldPersistGoingBackToSomeRoot);
    Runner runner;
    for (auto oneTestToRun : testsToRun) {
         runner.run(oneTestToRun);
    }

    runner.showStats();
}

