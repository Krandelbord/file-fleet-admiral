#include "CompareByName.h"
#include "config.h"

CompareByName::CompareByName() {
}

CompareResult CompareByName::compare(const FileListElement& first, const FileListElement& second) const {
    gfm_debug("porownywanie by name\n");
    if (first.getFileName().lowercase() < second.getFileName().lowercase()) {
        return CompareResult::SECOND_IS_LESS;
    } else {
        return CompareResult::FIRST_IS_LESS;
    }
}

CompareByName::~CompareByName() {
}
