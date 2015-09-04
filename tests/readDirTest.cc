#include <snowhouse/snowhouse.h>
#include "../PathResolver.h"
using namespace snowhouse;

void checkDirGeneration(const Glib::ustring& startDir, const Glib::ustring& cdCommand, const Glib::ustring expected) {
    PathResolver path(startDir);
    path.changeDirBy(cdCommand);

    try {
        Assert::That(path.toString(), Equals(expected));
    } catch (AssertionException& ex) {
        std::cout << ex.GetMessage() << std::endl;
    }
}

int main() {
    checkDirGeneration("/home/emil/Documents", "notes", "/home/emil/Documents/notes");
}

