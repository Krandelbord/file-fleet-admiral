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

class Runner {
    public :
        void run(bool runResultWasSuccess) {
            totalCount++;
            if (runResultWasSuccess) {
                successCount++;
            }
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
};

int main() {
    Runner runner;

    runner.run(checkDirGeneration("/home/emil/Documents", "notes", "/home/emil/Documents/notes"));
    runner.run(checkDirGeneration("/home/emil/Documents", "..", "/home/emil"));
    runner.run(checkDirGeneration("/", "..", "/"));
    runner.run(checkDirGeneration("/home", "..", "/"));
    runner.run(checkDirGeneration("/", "home", "/home"));

    runner.run(shouldPersistSelection());
    runner.run(shouldPersist3LevelSelection());
    runner.run(shouldPersistDirUpSelection());
    runner.showStats();
}

