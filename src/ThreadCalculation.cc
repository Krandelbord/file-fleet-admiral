#include "ThreadCalculation.h"
#include <sys/stat.h>
#include <giomm.h>
#include <gdkmm.h>
#include <gtkmm.h>
#include "config.h"
#include "gui/SizeFormatterFactory.h"
#include "gui/FileWithInode.h"

auto ThreadCalculation::readFileSize(const std::string& filePathToReadSize) {
    struct stat_result {__off_t fileSizeInBytes; __ino_t inodeNumber;};
    struct stat statFile {};
    __off_t fileSize = 0;
    __ino_t inodeNumber = UNDEFINED_INODE;
    int err = stat(filePathToReadSize.c_str(), &statFile);
    if (err != 0) {
        fileSize = 0;
    } else {
        fileSize = statFile.st_size;
        inodeNumber = statFile.st_ino;
    }
    return stat_result{fileSize, inodeNumber};
}

void ThreadCalculation::threadFunction(std::shared_ptr<ThreadMessage> threadMessage) {
    const std::shared_ptr<SizeFormatter> sizeFormatter = SizeFormatterFactory::createFromConfig();
    Glib::ustring dirToRead = threadMessage->getDirToRead();
    int readPositionsCount = 0;

    std::vector<FileListElement> dirContent;
    //this is heavy work separate thread function
    if (Glib::file_test(dirToRead, Glib::FileTest::FILE_TEST_IS_DIR)) {
        Glib::Dir dir(dirToRead);
        for (Glib::DirIterator dirIter = dir.begin(); dirIter != dir.end(); ++dirIter) {
            std::string nextElemInDir = *dirIter;
            std::string path = Glib::build_filename(dirToRead, nextElemInDir);
            //Glib::usleep(101000);

            if (!nextElemInDir.empty()) {
                auto statData = readFileSize(path);
                FileType fileType = readFileType(path);
                const std::string formattedSize = sizeFormatter->formatSize(statData.fileSizeInBytes);
                const Glib::RefPtr<Gio::Icon> &icon = Gio::content_type_get_icon("text/python");
                const Glib::RefPtr<Gdk::Pixbuf> &anIcon = getIconForFile(path);
                dirContent.emplace_back(FileListElement(nextElemInDir, statData.fileSizeInBytes, fileType, formattedSize, anIcon, statData.inodeNumber));
                readPositionsCount++;
            }
            if (threadMessage->shouldCancelWorkAsync()) {
                return;
            }
        }
    }
    threadMessage->getSortChain().sort(dirContent);
    threadMessage->addNewDataAsync(dirContent);
    threadMessage->notifyAllThreadsOfWorkFinish();
    gfm_debug("finish of calculation for dir %s, found %d\n", dirToRead.c_str(), readPositionsCount);
}

Glib::RefPtr<Gdk::Pixbuf> ThreadCalculation::getIconForFile(const Glib::ustring& filePath) {
    //File is a custom class
    static Glib::RefPtr<Gtk::IconTheme> iconTheme = Gtk::IconTheme::get_default();
//    Glib::ustring sPath = Glib::build_filename(filePath.getDirPath(), f->getName());
    Glib::RefPtr<Gio::File> gioFile = Gio::File::create_for_path(filePath);
    Glib::RefPtr<Gio::FileInfo> info = gioFile->query_info();
//    Glib::RefPtr<Gio::Icon> icon = info->get_icon();
//
//    Gtk::IconInfo iconInfo = iconTheme->lookup_icon(icon, 3, Gtk::ICON_LOOKUP_USE_BUILTIN);
//    return iconInfo.load_icon();
    return Gdk::Pixbuf::create_from_file("/usr/share/icons/gnome/22x22/apps/access.png");
}

FileType ThreadCalculation::readFileType(const std::string& pathToReadFileType) {
    FileType fileType = FileType::REGULAR_FILE;
    if (Glib::file_test(pathToReadFileType, Glib::FILE_TEST_IS_DIR)) {
        fileType = FileType::DIRECTORY;
    }

    return fileType;
}

bool sortByNameDirsFirst(FileListElement first, FileListElement second) {
    //dirs first
    if (first.getFileType() == FileType::DIRECTORY && second.getFileType() == FileType::REGULAR_FILE) {
        return true;
    } else if (first.getFileType() == FileType::REGULAR_FILE && second.getFileType() == FileType::DIRECTORY) {
        return false;
    }
    return first.getFileName().lowercase() < second.getFileName().lowercase();
}

