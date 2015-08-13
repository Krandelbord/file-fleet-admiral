#ifndef SETTINGS_H
#define SETTINGS_H

#include <glibmm/ustring.h>
#include "Rectangle.h"

class Settings {
    public :
        Settings();
        void saveInteger(const Glib::ustring &name, int integer_to_save);
        int readInteger(const Glib::ustring &name);
        int readPanedPosition();

        Rectangle readWindowSize();
        void saveWindowSize(Rectangle rectWinSize);
        
        ~Settings();
        
    private:
        GKeyFile *m_key_file;
        char *m_file;
    
};

#endif /** SETTINGS_H */
