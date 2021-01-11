#include "FileListElement.h"
#include "../PathResolver.h"
#import <gtkmm.h>

FileListElement::FileListElement(const Glib::ustring& aFileName, __off_t aFileSizeInBytes,
        FileType aFileType, std::string sizeFormatted, const Glib::RefPtr<const Gdk::Pixbuf>& icon, __ino_t inodeNumber) {
    this->fileName = Glib::ustring(aFileName);
    this->fileSizeInBytes = aFileSizeInBytes;
    this->fileType = aFileType;
    this->fileSizeForDisplay = sizeFormatted;
    this->inodeNumber = inodeNumber;
    this->icon = icon->copy();
}

const Glib::ustring& FileListElement::getFileName() const {
    return fileName;
}

__off_t FileListElement::getFileSizeInBytes() const {
    return fileSizeInBytes;
}

FileType FileListElement::getFileType() const {
    return fileType;
}

Glib::ustring FileListElement::getFileSizeForDisplay() const {
    return fileSizeForDisplay;
}

FileListElement FileListElement::createParentDir() {
    const Glib::RefPtr<Gio::Icon> &ptr = Gio::Icon::create("none");
    Glib::RefPtr<const Gdk::Pixbuf> pixBufIcon = Gdk::Pixbuf::create_from_file("/usr/share/icons/Moka/22x22/places/debian.png");
    FileListElement toParentDir(PARENT_DIR_SYMBOL, 0, FileType::PARENT_DIR, "", pixBufIcon);
    return toParentDir;
}

const std::string FileListElement::toString() const {
    return fileName;
}

__ino_t FileListElement::getInodeNumber() const {
    return inodeNumber;
}

const Glib::RefPtr<const Gdk::Pixbuf> &FileListElement::getIcon() const {
    return icon;
}
