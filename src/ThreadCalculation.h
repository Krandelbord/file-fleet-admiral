#ifndef THREAD_CALCULATION_H
#define THREAD_CALCULATION_H

#include <memory>
#include "ThreadMessage.h"

/**
 * Class that does heavy computation is separate thread
 */
class ThreadCalculation {
    public:
        void threadFunction(std::shared_ptr<ThreadMessage> threadMessage);
    private:
        auto readFileSize(const std::string& filePathToReadSize);
        FileType readFileType(const std::string& pathToReadFileType);
        void sortData(std::vector<FileListElement>& dataToSort);
        static Glib::RefPtr<Gdk::Pixbuf> getIconForFile(const Glib::ustring &filePath);
};

#endif /** THREAD_CALCULATION_H */
