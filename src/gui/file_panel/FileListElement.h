#ifndef FILE_LIST_ELEMENT_H
#define FILE_LIST_ELEMENT_H

#include <glibmm.h>
#include "../FileType.h"

/**
 * Represents element in file list GUI
 */
class FileListElement {
    public:
    FileListElement(const Glib::ustring &fileName,
                    __off_t fileSizeInBytes,
                    FileType fileType,
                    std::string sizeFormatted,
                    __ino_t inodeNumber = -1);

        static FileListElement createParentDir();

        const Glib::ustring& getFileName() const;
        __off_t getFileSizeInBytes() const;
        Glib::ustring getFileSizeForDisplay() const;
        const FileType getFileType() const;
        const std::string toString() const;
        __ino_t getInodeNumber() const;

private:
        Glib::ustring fileName;
        __off_t fileSizeInBytes;
        __ino_t inodeNumber;
        FileType fileType;
        std::string fileSizeForDisplay;
};

#endif /** FILE_LIST_ELEMENT_H **/
