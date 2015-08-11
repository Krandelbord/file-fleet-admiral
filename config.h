#ifndef CONFIG_H

#ifdef DEBUG
#include <glib.h>
#  define gfm_debug(args...) g_print (args)
#else
#  define gfm_debug(args...) ;
#endif


#endif /* CONFIG_H */
