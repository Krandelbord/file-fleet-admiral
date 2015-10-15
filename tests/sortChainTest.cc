/**
 * Tests sorting chain
 */
#include "../SortChain.h"
#include "../CompareByName.h"
#include "Asserts.h"

const Glib::ustring convertVectorToString(std::vector<FileListElement> dataToConcatenate) {
    std::stringstream concatenatedFiles;
    for (FileListElement oneElement : dataToConcatenate) {
        concatenatedFiles << oneElement.toString() << std::endl;
    }
    return concatenatedFiles.str();
}

int main() {
    SortChain sortChain(std::make_shared<CompareByName>());
    std::vector<FileListElement> toSort;
    toSort.push_back(FileListElement("firstFile.jpg", 0, FileType::REGULAR_FILE, ""));
    toSort.push_back(FileListElement("secondFile.jpg", 0, FileType::REGULAR_FILE, ""));
    toSort.push_back(FileListElement("anotherFile.jpg", 0, FileType::REGULAR_FILE, ""));

    sortChain.sort(toSort);
    Asserts::assertEquals("Elements sort order not correct", "oko", convertVectorToString(toSort));
    return 0;
}

