#include <iostream>
#include "Asserts.h"
#include "../PathResolver.h"
#include "../SelectionHistory.h"

#define COLOR_RESET "\x1b[0m"
#define COLOR_RED   "\x1b[31;1m"
#define COLOR_GREEN "\x1b[32;1m"
/**
 * Returns true for cussess 
 */
bool checkDirGeneration(const Glib::ustring& startDir, const Glib::ustring& cdCommand, const Glib::ustring expected) {
    PathResolver path(startDir);
    path.changeDirBy(cdCommand);

    return Asserts::assertEquals("Values not equal", path.toString(), expected);
}

bool shouldPersist3LevelSelection() {
    SelectionHistory selHistory("/home/emil/music");
    selHistory.changeDirBy("Judas Priest");
    selHistory.changeDirBy("1993 - Metal Works");
    selHistory.changeDirBy("CD2");

    Glib::ustring expectedSelection("Judas Priest");
    return Asserts::assertEquals("Values not equal", selHistory.getSelectionForDir("/home/emil/music"), expectedSelection);
}

bool shouldPersistDirUpSelection() {
    SelectionHistory selHistory("/home/emil/music");
    selHistory.changeDirBy("Judas Priest");
    selHistory.changeDirBy("1993 - Metal Works");
    selHistory.changeDirBy("..");

    Glib::ustring expectedSelection("1993 - Metal Works");
    return Asserts::assertEquals("Values not equal", selHistory.getSelectionForDir("/home/emil/music/Judas Priest"), expectedSelection);
}

bool shouldPersistSelection() {
    SelectionHistory selHistory("/home/emil/Documents");
    selHistory.changeDirBy("drawings");

    Glib::ustring expectedSelection("drawings");

    return Asserts::assertEquals("Values not equal", selHistory.getSelectionForDir("/home/emil/Documents"), expectedSelection);
}

bool shouldPersistGoingBackToSomeRoot() { 
    SelectionHistory selHistory("/home/emil/music");
    selHistory.changeDirBy("Judas Priest");
    selHistory.changeDirBy("..");
    selHistory.changeDirBy("Iron Maiden");
    selHistory.changeDirBy("..");

    return Asserts::assertEquals("Values not equal", "Iron Maiden", selHistory.getSelectionForDir("/home/emil/music"));
}

class Runner {
    public :
       
        void run(std::function<bool()> oneTestFunction) {
            doRun(oneTestFunction());
        }

        void showStats() {
            if (totalCount == successCount) {
               std::cout << COLOR_GREEN;
            } else {
               std::cout << COLOR_RED;
            }
	    std::cout << "Tests finished. Success " << successCount << " of " << totalCount << COLOR_RESET << std::endl ;
        }
    private :
        unsigned int totalCount = 0;
        unsigned int successCount = 0;

        void doRun(bool runResultWasSuccess) {
            totalCount++;
            if (runResultWasSuccess) {
                successCount++;
            }
        }

};

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

