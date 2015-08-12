#ifndef SETTINGS_H
#define SETTINGS_H

#include <glibmm/ustring.h>

class Settings {
    public :
        Settings();
        void saveInteger(const Glib::ustring &name, int integer_to_save);
        int readInteger(const Glib::ustring &name) const;
        int readWindowSize() const;
        void saveWindowSize(int valueToSave);
        
        ~Settings();
        
    private:
        GKeyFile *m_key_file;
        char *m_file;
    
};

#endif /** SETTINGS_H */
