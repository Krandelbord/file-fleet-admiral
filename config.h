#ifndef CONFIG_H

#define APPLICATION_NAME "Gtkmm File Manager"
#define APPLICATION_VERSION "0.1"

#ifdef DEBUG
#include <glib.h>
#include <chrono>
#include <ctime>
#  define gfm_debug(args...) g_print("%s:", std::asctime(std::chrono::system_clock::now()); g_print (args)
#else
#  define gfm_debug(args...) ;
#endif


#endif /* CONFIG_H */
