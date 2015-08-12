#include "Settings.h"
#include <glibmm/keyfile.h>

#define MAIN_CATEGORY_NAME "main-settings"

Settings::Settings() {
    m_key_file = g_key_file_new();
	
	const gchar *konf_rootdir = g_get_user_config_dir();
	m_file = g_build_filename(konf_rootdir, "gfm.cfg", NULL);
	g_key_file_load_from_file(m_key_file, m_file, G_KEY_FILE_KEEP_COMMENTS, NULL);
}


int Settings::readInteger(const Glib::ustring &name) const {
	return g_key_file_get_integer(m_key_file, MAIN_CATEGORY_NAME, name.c_str(), NULL);
}

void Settings::saveInteger(const Glib::ustring &name, int value) {
	g_key_file_set_integer(m_key_file, MAIN_CATEGORY_NAME, name.c_str(), value);
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
