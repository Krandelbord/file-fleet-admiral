#ifndef FILE_LIST_ELEMENT_H
#define FILE_LIST_ELEMENT_H

#include <glibmm.h>

/**
 * Represents element in file list
 */
class FileListElement {
    public:
        FileListElement(const Glib::ustring& fileName, uint64_t fileSizeInBytes);

        const Glib::ustring& getFileName() const;
        uint64_t getFileSizeInBytes() const;
    private:
        Glib::ustring fileName;
        uint64_t fileSizeInBytes;
};

#endif /** FILE_LIST_ELEMENT_H **/
