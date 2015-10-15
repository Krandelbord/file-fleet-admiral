/**
 * Tests sorting chain
 */
#include "../SortChain.h"
#include "../CompareByName.h"
#include "Asserts.h"
#include "Runner.h"

bool shouldSortFilesByName();

const Glib::ustring convertVectorToString(std::vector<FileListElement> dataToConcatenate) {
    std::stringstream concatenatedFiles;
    for (FileListElement oneElement : dataToConcatenate) {
        concatenatedFiles << oneElement.toString() << std::endl;
    }
    return concatenatedFiles.str();
}

const bool assertElementOrder(const std::string &expectedOrder, std::vector<FileListElement> &toCheck) {
    return Asserts::assertEquals("Elements sort order not correct",
                                 expectedOrder,
                                 convertVectorToString(toCheck));
}

bool shouldSortFilesByName() {
    SortChain sortChain(std::make_shared<CompareByName>());
    std::vector<FileListElement> toSort;
    toSort.push_back(FileListElement("firstFile.jpg", 0, FileType::REGULAR_FILE, ""));
    toSort.push_back(FileListElement("secondFile.jpg", 0, FileType::REGULAR_FILE, ""));
    toSort.push_back(FileListElement("anotherFile.jpg", 0, FileType::REGULAR_FILE, ""));

    sortChain.sort(toSort);

    return assertElementOrder("anotherFile.jpg\n"
                               "firstFile.jpg\n"
                               "secondFile.jpg\n", toSort);
}

int main() {
    Runner testRunner;
    testRunner.run(shouldSortFilesByName);
    testRunner.showStats();
    return 0;
}
