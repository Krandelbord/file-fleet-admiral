#ifndef FILE_LIST_ELEMENT_H
#define FILE_LIST_ELEMENT_H

#include <glibmm.h>
#include "FileType.h"

/**
 * Represents element in file list
 */
class FileListElement {
    public:
        FileListElement(const Glib::ustring& fileName, uint64_t fileSizeInBytes, 
                FileType fileType);

        static FileListElement createParentDir();

        const Glib::ustring& getFileName() const;
        uint64_t getFileSizeInBytes() const;
        Glib::ustring getFileSizeForDisplay() const;
        const FileType getFileType() const;

    private:
        Glib::ustring fileName;
        uint64_t fileSizeInBytes;
        FileType fileType;
};

#endif /** FILE_LIST_ELEMENT_H **/
