#ifndef FILE_LIST_ELEMENT_H
#define FILE_LIST_ELEMENT_H

#include <glibmm.h>
#include <gdkmm.h>
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
                    const Glib::RefPtr<const Gdk::Pixbuf>& icon,
                    __ino_t inodeNumber = -1);

        static FileListElement createParentDir();

        const Glib::ustring& getFileName() const;
        __off_t getFileSizeInBytes() const;
        Glib::ustring getFileSizeForDisplay() const;
        FileType getFileType() const;
        std::string toString() const;
        __ino_t getInodeNumber() const;
        const Glib::RefPtr<const Gdk::Pixbuf> &getIcon() const;

private:
        Glib::ustring fileName;
        __off_t fileSizeInBytes;
        __ino_t inodeNumber;
        FileType fileType;
        std::string fileSizeForDisplay;
        Glib::RefPtr<const Gdk::Pixbuf> icon;
};

#endif /** FILE_LIST_ELEMENT_H **/
