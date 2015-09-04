#include <snowhouse/snowhouse.h>
#include "../PathResolver.h"
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

    runner.showStats();
}

