#ifndef FILE_FLEET_ADMIRAL_FILEWITHINODE_H
#define FILE_FLEET_ADMIRAL_FILEWITHINODE_H


#include <glibmm/ustring.h>

class FileWithInode {
public :
    FileWithInode();
    FileWithInode(Glib::ustring fileName,
                  __ino_t inodeNumber);

    const Glib::ustring &getFileName() const;

    __ino_t getInodeNumber() const;

private:
    Glib::ustring fileName;
    __ino_t inodeNumber = -1;
};


#endif //FILE_FLEET_ADMIRAL_FILEWITHINODE_H
