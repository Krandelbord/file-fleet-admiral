#ifndef CONFIG_H

#define APPLICATION_NAME "Gtkmm File Manager"
#define APPLICATION_VERSION "0.1"

#ifdef DEBUG
#include <glib.h>
#include "debug.h"
#  define gfm_debug(args...) debug_with_time(); g_print (args)
#else
#  define gfm_debug(args...) ;
#endif


#endif /* CONFIG_H */
