#include "FileListElement.h"

FileListElement::FileListElement(const Glib::ustring& aFileName, uint64_t aFileSizeInBytes) {
    this->fileName = Glib::ustring(aFileName);
    this->fileSizeInBytes = aFileSizeInBytes;
}

const Glib::ustring& FileListElement::getFileName() const {
    return fileName;
}

uint64_t FileListElement::getFileSizeInBytes() const {
    return fileSizeInBytes;
}

