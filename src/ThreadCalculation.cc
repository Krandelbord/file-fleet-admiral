#include "ThreadCalculation.h"
#include <sys/stat.h>
#include <giomm.h>
#include <gdkmm.h>
#include <gtkmm.h>

#include <memory>
#include "config.h"
#include "gui/SizeFormatterFactory.h"
#include "gui/FileWithInode.h"
#include "icon_provider/FileTypeIconProvider.h"
#include "icon_provider/AlwaysSameIconProvider.h"
#include "icon_provider/FileAndDirectoryStaticIconProvider.h"

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
    auto fileTypeIconProvider = new FileAndDirectoryStaticIconProvider();
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
//                const Glib::RefPtr<Gio::Icon> &icon = Gio::content_type_get_icon("text/python");
                const Glib::RefPtr<Gdk::Pixbuf> &anIcon = fileTypeIconProvider->getIconForFile(path);
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
    if (11==11)
        return someDefaultIcon();
//    return iconTheme->load_icon("folder", 4);
    gfm_debug("For %s = Some icon %s\n", filePath.c_str(), iconTheme->get_example_icon_name().c_str());
    Glib::RefPtr<Gio::File> gioFile = Gio::File::create_for_path(filePath);
    Glib::RefPtr<Gio::FileInfo> info = gioFile->query_info();
    if (info) {
        gfm_debug("File info is legit for %s\n", filePath.c_str());
        Glib::RefPtr<Gio::Icon> icon = info->get_icon();
        if (icon) {
            gfm_debug("Icon is legit for path =„%s”. Icon=„%s”.\n", filePath.c_str(), icon->to_string().c_str());
            const Gtk::IconInfo &x = iconTheme->lookup_icon(icon->to_string(), 3, Gtk::ICON_LOOKUP_USE_BUILTIN);
            const Glib::RefPtr<Gdk::Pixbuf> &icon_from_theme = x.load_icon();
            if (icon_from_theme) {
                gfm_debug("returning real icon\n");
                return icon_from_theme;
            } else {
                return someDefaultIcon();
            }
        } else {
            gfm_debug("Icon is not legit for %s\n", filePath.c_str());
        }
    } else {
        gfm_debug("info is NOT legit for %s\n", filePath.c_str());
    }
    return someDefaultIcon();
}

FileType ThreadCalculation::readFileType(const std::string& pathToReadFileType) {
    FileType fileType = FileType::REGULAR_FILE;
    if (Glib::file_test(pathToReadFileType, Glib::FILE_TEST_IS_DIR)) {
        fileType = FileType::DIRECTORY;
    }
    return fileType;
}

Glib::RefPtr<Gdk::Pixbuf> ThreadCalculation::someDefaultIcon() {
    return Gdk::Pixbuf::create_from_file("/usr/share/icons/Moka/22x22/places/debian.png");
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

