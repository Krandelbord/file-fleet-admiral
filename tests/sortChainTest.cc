/**
 * Tests sorting chain
 */
#include "../SortChain.h"
#include "../CompareByName.h"
#include "Asserts.h"
#include "Runner.h"
#include "../CompareDirsFirst.h"
#include "../CompareBySize.h"

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

bool shouldSortDirsFirst() {
    SortChain sortChain(std::make_shared<CompareDirsFirst>());
    sortChain.addSorting(std::make_shared<CompareByName>());
    std::vector<FileListElement> toSort;
    toSort.push_back(FileListElement("firstFile.jpg", 0, FileType::REGULAR_FILE, ""));
    toSort.push_back(FileListElement("SOME_DIR", 0, FileType::DIRECTORY, ""));
    toSort.push_back(FileListElement("secondFile.jpg", 0, FileType::REGULAR_FILE, ""));
    toSort.push_back(FileListElement("anotherFile.jpg", 0, FileType::REGULAR_FILE, ""));

    sortChain.sort(toSort);

    return assertElementOrder("SOME_DIR\n"
                              "anotherFile.jpg\n"
                              "firstFile.jpg\n"
                              "secondFile.jpg\n", toSort);
}

bool shouldSortInReverseOrder() {
    SortChain sortChain(std::make_shared<CompareDirsFirst>());
    sortChain.addSorting(std::make_shared<CompareByName>());
    sortChain.reverseOrder();
    std::vector<FileListElement> toSort;
    toSort.push_back(FileListElement("firstFile.jpg", 0, FileType::REGULAR_FILE, ""));
    toSort.push_back(FileListElement("SOME_DIR", 0, FileType::DIRECTORY, ""));
    toSort.push_back(FileListElement("secondFile.jpg", 0, FileType::REGULAR_FILE, ""));
    toSort.push_back(FileListElement("anotherFile.jpg", 0, FileType::REGULAR_FILE, ""));

    sortChain.sort(toSort);
    return assertElementOrder("secondFile.jpg\n"
            "firstFile.jpg\n"
            "anotherFile.jpg\n"
            "SOME_DIR\n", toSort);
}

bool shouldSortBySizeDirsFirst() {
    SortChain sortChain(std::make_shared<CompareDirsFirst>());
    sortChain.addSorting(std::make_shared<CompareBySize>());
    sortChain.reverseOrder();
    std::vector<FileListElement> toSort;
    toSort.push_back(FileListElement("firstFile.jpg", 150, FileType::REGULAR_FILE, ""));
    toSort.push_back(FileListElement("SOME_DIR", 0, FileType::DIRECTORY, ""));
    toSort.push_back(FileListElement("secondFile.jpg", 200, FileType::REGULAR_FILE, ""));
    toSort.push_back(FileListElement("anotherFile.jpg", 400, FileType::REGULAR_FILE, ""));

    sortChain.sort(toSort);
    return assertElementOrder("anotherFile.jpg\n"
                                      "secondFile.jpg\n"
                                      "firstFile.jpg\n"
                                      "SOME_DIR\n", toSort);
}

int main() {
    Runner testRunner;
    testRunner.run(shouldSortFilesByName);
    testRunner.run(shouldSortDirsFirst);
    testRunner.run(shouldSortInReverseOrder);
    testRunner.run(shouldSortBySizeDirsFirst);
    testRunner.showStats();
    return 0;
}
