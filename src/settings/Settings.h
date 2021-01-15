#ifndef SETTINGS_H
#define SETTINGS_H

static const char *const SIZE_FORMAT_IN_BYTES = "IN_BYTES";
static const int DEFAULT_LABEL_PADDING = 8;
static const int DEFAULT_POPUP_MARGIN = 2*DEFAULT_LABEL_PADDING;

#include <glibmm/ustring.h>
#include <glibmm.h>
#include "../gui/Rectangle.h"
#include "FileIconsRenderingType.h"

class Settings {
    public :
        Settings();
        void saveInteger(const Glib::ustring& name, int integer_to_save);
        int readInteger(const Glib::ustring& name) const;
        int readPanedPosition() const;
        Glib::ustring getRightDirPath() const;

        Rectangle readWindowSize();
        std::string readSizeFormat();
        void saveWindowSize(Rectangle rectWinSize);
        void savePanedPosition(int panedPositionToSave);
        void saveRightPanelDir(const Glib::ustring& dirToSave);
        void saveSizeFormat(Glib::ustring newSizeFormatToSave);

        ~Settings();

        const static int DEFAULT_ICON_SIZE = 3;
        const static FileIconsRenderingType iconsRenderingType = FileIconsRenderingType::FILE_TYPE_PER_ICON;

private:
        int readWindowWidth() const;
        Glib::ustring readStringConfigValue(const Glib::ustring& paramToRead) const;
        void saveString(const Glib::ustring& name, const Glib::ustring& value);
        std::string readStringConfigValueWithDefault(Glib::ustring keyToRead, Glib::ustring defaultValue);

        GKeyFile *m_key_file;
        char *m_file;
};

#endif /** SETTINGS_H */
