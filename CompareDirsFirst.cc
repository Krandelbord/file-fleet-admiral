#include "CompareDirsFirst.h"
#include "CompareByName.h"

CompareResult CompareDirsFirst::compare(const FileListElement& first, const FileListElement& second) const {
    if (first.getFileType() != FileType::DIRECTORY && second.getFileType() == FileType::DIRECTORY) {
        return CompareResult::FIRST_IS_LESS;
    } else if (second.getFileType() != FileType::DIRECTORY && first.getFileType() == FileType::DIRECTORY) {
        return CompareResult::SECOND_IS_LESS;
    } else if (bothAreDirs(first, second)) {
        CompareByName cmpByName;
        return cmpByName.compare(first, second);
    }
    return CompareResult::UNDEFINED;
}

CompareDirsFirst::~CompareDirsFirst() {
}

bool CompareDirsFirst::bothAreDirs(const FileListElement &first, const FileListElement &second) const {
    return first.getFileType() == FileType::DIRECTORY && second.getFileType() == FileType::DIRECTORY;
}
