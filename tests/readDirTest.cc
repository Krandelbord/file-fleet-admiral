#include <snowhouse/snowhouse.h>
#include "../PathResolver.h"
#include "../SelectionHistory.h"

using namespace snowhouse;

/**
 * Returns true for cussess 
 */
bool checkDirGeneration(const Glib::ustring& startDir, const Glib::ustring& cdCommand, const Glib::ustring expected) {
    PathResolver path(startDir);
    path.changeDirBy(cdCommand);

    try {
        Assert::That(path.toString(), Equals(expected));
    } catch (AssertionException& ex) {
        std::cout << ex.GetMessage() << std::endl;
        return false;
    }
    return true;
}

bool shouldPersist3LevelSelection() {
    SelectionHistory selHistory("/home/emil/music");
    selHistory.changeDirBy("Judas Priest");
    selHistory.changeDirBy("1993 - Metal Works");
    selHistory.changeDirBy("CD2");

    Glib::ustring expectedSelection("Judas Priest");
    try {
        Assert::That(selHistory.getSelectionForDir("/home/emil/music"), Equals(expectedSelection));
    } catch (AssertionException& ex) {
        std::cout << ex.GetMessage() << std::endl;
        return false;
    }
    return true;
}

bool shouldPersistDirUpSelection() {
    SelectionHistory selHistory("/home/emil/music");
    selHistory.changeDirBy("Judas Priest");
    selHistory.changeDirBy("1993 - Metal Works");
    selHistory.changeDirBy("..");

    Glib::ustring expectedSelection("1993 - Metal Works");
    try {
        Assert::That(selHistory.getSelectionForDir("/home/emil/music/Judas Priest"), Equals(expectedSelection));
    } catch (AssertionException& ex) {
        std::cout << ex.GetMessage() << std::endl;
        return false;
    }
    return true;
}

bool shouldPersistSelection() {
    SelectionHistory selHistory("/home/emil/Documents");
    selHistory.changeDirBy("drawings");

    Glib::ustring expectedSelection("drawings");
    try {
        Assert::That(selHistory.getSelectionForDir("/home/emil/Documents"), Equals(expectedSelection));
    } catch (AssertionException& ex) {
        std::cout << ex.GetMessage() << std::endl;
        return false;
    }
    return true;
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
            std::cout << "Tests finished. Success " << successCount << " of " << totalCount << std::endl;
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

