#ifndef FILE_LIST_ELEMENT_H
#define FILE_LIST_ELEMENT_H

#include <glibmm.h>
#include "FileType.h"

/**
 * Represents element in file list GUI
 */
class FileListElement {
    public:
        FileListElement(const Glib::ustring& fileName, __off_t fileSizeInBytes,
                FileType fileType);

        static FileListElement createParentDir();

        const Glib::ustring& getFileName() const;
        __off_t getFileSizeInBytes() const;
        Glib::ustring getFileSizeForDisplay() const;
        const FileType getFileType() const;

    private:
        Glib::ustring fileName;
        __off_t fileSizeInBytes;
        FileType fileType;
};

#endif /** FILE_LIST_ELEMENT_H **/
