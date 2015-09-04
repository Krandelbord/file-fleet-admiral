#include "FileListElement.h"
#include "PathResolver.h"

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

Glib::ustring FileListElement::getFileSizeForDisplay() const {
    std::ostringstream out;
    out << fileSizeInBytes;
    return out.str();
}

FileListElement FileListElement::createParentDir() {
    FileListElement toParentDir(PARENT_DIR_SYMBOL, 0, FileType::PARENT_DIR);
    return toParentDir;
}
