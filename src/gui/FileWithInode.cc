
#include "FileWithInode.h"
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
