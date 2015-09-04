#include "FileListElement.h"

FileListElement::FileListElement(const Glib::ustring& aFileName, uint64_t aFileSizeInBytes,
        FileType aFileType) {
    this->fileName = Glib::ustring(aFileName);
    this->fileSizeInBytes = aFileSizeInBytes;
    this->fileType = aFileType;
}

const Glib::ustring& FileListElement::getFileName() const {
    return fileName;
}

uint64_t FileListElement::getFileSizeInBytes() const {
    return fileSizeInBytes;
}

const FileType FileListElement::getFileType() const {
    return fileType;
}

FileListElement FileListElement::createParentDir() {
    FileListElement toParentDir("..", 0, FileType::DIRECTORY);
    return toParentDir;
}
