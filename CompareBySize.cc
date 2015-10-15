#include "CompareBySize.h"

CompareBySize::CompareBySize() {
}

CompareResult CompareBySize::compare(const FileListElement& first, const FileListElement& second) const {
    if (first.getFileSizeInBytes() < second.getFileSizeInBytes()) {
        return CompareResult::SECOND_IS_LESS;
    } else {
        return CompareResult::FIRST_IS_LESS;
    }
}
