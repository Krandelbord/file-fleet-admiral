#ifndef FILE_LIST_ELEMENT_H
#define FILE_LIST_ELEMENT_H

#include <glibmm.h>

/**
 * Represents element in file list
 */
class FileListElement {
    public:
        FileListElement(const Glib::ustring& fileName, int fileSizeInBytes);

        const Glib::ustring& getFileName() const;
    private:
        Glib::ustring fileName;
        int fileSizeInBytes;
};

#endif /** FILE_LIST_ELEMENT_H **/
