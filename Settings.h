#ifndef SETTINGS_H
#define SETTINGS_H

#include <glibmm/ustring.h>
#include "Rectangle.h"

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
        void saveSizeFormat(const Glib::ustring newSizeFormatToSave);

        ~Settings();
private:
        int readWindowWidth() const;
        Glib::ustring readStringConfigValue(const Glib::ustring& paramToRead) const;
        void saveString(const Glib::ustring& name, const Glib::ustring& value);
        GKeyFile *m_key_file;
        char *m_file;

};

#endif /** SETTINGS_H */
