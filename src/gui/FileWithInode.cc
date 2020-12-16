
#include "FileWithInode.h"
#include "../config.h"
#include <utility>

FileWithInode::FileWithInode() {

}

FileWithInode::FileWithInode(Glib::ustring fileName, __ino_t inodeNumber) : fileName(std::move(fileName)),
                                                                            inodeNumber(inodeNumber) {}

const Glib::ustring &FileWithInode::getFileName() const {
    return fileName;
}

__ino_t FileWithInode::getInodeNumber() const {
    return inodeNumber;
}

Glib::ustring FileWithInode::toString() const {
    return Glib::ustring::compose<>("FileWithInode{inode=%1, name=„%2”}",
                                    inodeNumber, fileName);
}

bool FileWithInode::matchesInode(__ino_t searchedInodeNumber) const {
    if (inodeNumber != UNDEFINED_INODE && searchedInodeNumber != UNDEFINED_INODE) {
        return inodeNumber == searchedInodeNumber;
    } else {
        return false;
    }
}
