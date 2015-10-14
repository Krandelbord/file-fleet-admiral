#include "Settings.h"
#include <glibmm/keyfile.h>
#include "config.h"
#include <glibmm.h>

#define MAIN_CATEGORY_NAME "main-settings"
#define NO_ERROR_HANDLER NULL
#define DEFAULT_WINDOW_WIDTH 800

const Glib::ustring CONF_MAIN_WINDOW_SIZE_X = Glib::ustring("main_window_width");
const Glib::ustring CONF_MAIN_WINDOW_SIZE_Y = Glib::ustring("main_window_height");
const Glib::ustring CONF_MAIN_PANEL_SPLIT = Glib::ustring("panels_split");
const Glib::ustring CONF_RIGHT_PANEL_DIR = Glib::ustring("right_panel_last_dir");
const Glib::ustring CONF_SIZE_FORMAT = Glib::ustring("size_format");

Settings::Settings() {
    m_key_file = g_key_file_new();
	
	const gchar *konf_rootdir = g_get_user_config_dir();
	m_file = g_build_filename(konf_rootdir, "gfm.cfg", NULL);
	g_key_file_load_from_file(m_key_file, m_file, G_KEY_FILE_KEEP_COMMENTS, NO_ERROR_HANDLER);
}

int Settings::readInteger(const Glib::ustring &name) const {
    return g_key_file_get_integer(m_key_file, MAIN_CATEGORY_NAME, name.c_str(), NO_ERROR_HANDLER);
}

int Settings::readWindowWidth() const {
    gfm_debug("odczyt szerokosci \n");
    int readValueX = readInteger(CONF_MAIN_WINDOW_SIZE_X);
    if (readValueX == 0) {
        readValueX = DEFAULT_WINDOW_WIDTH;
    }
    return readValueX;
}

Rectangle Settings::readWindowSize() {
    gfm_debug("Odczyt wielkości okna\n");
    int readValueY = readInteger(CONF_MAIN_WINDOW_SIZE_Y);
    if (readValueY == 0) {
        readValueY = DEFAULT_WINDOW_WIDTH*0.7;
    }
    return Rectangle(readWindowWidth(), readValueY); 
}

void Settings::saveInteger(const Glib::ustring &name, int value) {
	return g_key_file_set_integer(m_key_file, MAIN_CATEGORY_NAME, name.c_str(), value);
}

void Settings::saveString(const Glib::ustring &name, const Glib::ustring& value) {
    if (!value.empty()) {
    	g_key_file_set_string(m_key_file, MAIN_CATEGORY_NAME, name.c_str(), value.c_str());
    }
}


void Settings::saveWindowSize(Rectangle rectToSave) {
    saveInteger(CONF_MAIN_WINDOW_SIZE_X, rectToSave.getWidth());
    saveInteger(CONF_MAIN_WINDOW_SIZE_Y, rectToSave.getHeight());
}

void Settings::savePanedPosition(int panedPositionToSave) {
    saveInteger(CONF_MAIN_PANEL_SPLIT, panedPositionToSave);
}


int Settings::readPanedPosition() const {
    int panelSplitRead = readInteger(CONF_MAIN_PANEL_SPLIT);
    if (panelSplitRead == 0) {
        return this->readWindowWidth()/2;
    } else {
        return panelSplitRead;
    }
}

Glib::ustring Settings::readStringConfigValue(const Glib::ustring& paramToRead) const {   
    gchar* readStringValue = g_key_file_get_string(m_key_file, MAIN_CATEGORY_NAME, paramToRead.c_str(), NO_ERROR_HANDLER);
    if (readStringValue!=NULL) {
        return Glib::ustring(readStringValue);
    } else {
        return "";
    }
}

Glib::ustring Settings::getRightDirPath() const {
    Glib::ustring rightPanelDir = readStringConfigValue(CONF_RIGHT_PANEL_DIR);
    if (rightPanelDir.empty()) {
        return Glib::get_current_dir();
    }
    return rightPanelDir;
}

void Settings::saveRightPanelDir(const Glib::ustring& dirToSave) {
    saveString(CONF_RIGHT_PANEL_DIR, dirToSave);
}

Settings::~Settings() {
	GError *blad = NULL;
	gchar *raw_kfile = g_key_file_to_data(m_key_file, NULL, &blad);
	
	FILE *plik_konfiguracji = fopen(m_file, "w+");
	if (!plik_konfiguracji) g_error("Nie mozna utworzyć domyśnego pliku konfigutracji w %s\n", m_file);
	fprintf(plik_konfiguracji, raw_kfile);

	/* Czystki: */
	fclose(plik_konfiguracji);
	g_free(raw_kfile);
	g_free(m_file);
	g_key_file_free(m_key_file);
}

std::string Settings::readSizeFormat() {
    return readStringConfigValueWithDfault(CONF_SIZE_FORMAT, SIZE_FORMAT_IN_BYTES);
}

void Settings::saveSizeFormat(const Glib::ustring newSizeFormatToSave) {
    saveString(CONF_SIZE_FORMAT, newSizeFormatToSave);
}

std::string Settings::readStringConfigValueWithDfault(const Glib::ustring keyToRead, const Glib::ustring defaultValue) {
    const Glib::ustring &valueRead = readStringConfigValue(keyToRead);
    if (valueRead.empty()) {
        return defaultValue;
    } else {
        return valueRead;
    }
}
