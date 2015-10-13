#include "FileListElement.h"
#include "PathResolver.h"

FileListElement::FileListElement(const Glib::ustring& aFileName, __off_t aFileSizeInBytes,
        FileType aFileType, std::string sizeFormatted) {
    this->fileName = Glib::ustring(aFileName);
    this->fileSizeInBytes = aFileSizeInBytes;
    this->fileType = aFileType;
    this->fileSizeForDisplay = sizeFormatted;
}

const Glib::ustring& FileListElement::getFileName() const {
    return fileName;
}

__off_t FileListElement::getFileSizeInBytes() const {
    return fileSizeInBytes;
}

const FileType FileListElement::getFileType() const {
    return fileType;
}

Glib::ustring FileListElement::getFileSizeForDisplay() const {
    return fileSizeForDisplay;
}

FileListElement FileListElement::createParentDir() {
    FileListElement toParentDir(PARENT_DIR_SYMBOL, 0, FileType::PARENT_DIR, "");
    return toParentDir;
}
