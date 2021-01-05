#ifndef FILE_FLEET_ADMIRAL_FILEWITHINODE_H
#define FILE_FLEET_ADMIRAL_FILEWITHINODE_H


#include <glibmm/ustring.h>
#include <memory>

const static __ino_t UNDEFINED_INODE = 0;

class FileWithInode {
public :
    FileWithInode();
    FileWithInode(Glib::ustring fileName,
                  __ino_t inodeNumber);
    const Glib::ustring &getFileName() const;
    __ino_t getInodeNumber() const;

    bool matchesInode(__ino_t searchedInodeNumber) const;
    Glib::ustring toString() const;

private:
    Glib::ustring fileName;
    __ino_t inodeNumber;
};
#endif //FILE_FLEET_ADMIRAL_FILEWITHINODE_H
