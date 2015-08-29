#include "CompareDirsFirst.h"

CompareResult CompareDirsFirst::compare(const FileListElement& first, const FileListElement& second) const {
    if (first.getFileType() != FileType::DIRECTORY && second.getFileType() == FileType::DIRECTORY) {
        return CompareResult::FIRST_IS_LESS;
    } else if (second.getFileType() != FileType::DIRECTORY && first.getFileType() == FileType::DIRECTORY) {
        return CompareResult::SECOND_IS_LESS;
    }
    return CompareResult::UNDEFINED;
}

CompareDirsFirst::~CompareDirsFirst() {
}
