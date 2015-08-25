#ifndef SETTINGS_H
#define SETTINGS_H

#include <glibmm/ustring.h>
#include "Rectangle.h"

class Settings {
    public :
        Settings();
        void saveInteger(const Glib::ustring &name, int integer_to_save);
        int readInteger(const Glib::ustring &name) const;
        int readPanedPosition() const;
        Glib::ustring getRightDirPath() const;

        Rectangle readWindowSize();
        void saveWindowSize(Rectangle rectWinSize);
        void savePanedPosition(int panedPositionToSave);

        ~Settings();
        
    private:
        int readWindowWidth() const;
        Glib::ustring readStringConfigValue(const Glib::ustring& paramToRead) const;

        GKeyFile *m_key_file;
        char *m_file;
    
};

#endif /** SETTINGS_H */
