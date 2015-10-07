#include "debug.h"
#include <glib.h>
#include <glibmm/date.h>
#include <glibmm/datetime.h>

void debug_with_time() {
    Glib::DateTime right_now = Glib::DateTime::create_now_local();
    right_now.add_days(2);
    GDateTime *gdt = right_now.gobj();
    gchar *date_formated = g_date_time_format(gdt, "%F %R:%S%");
   
    //the line below is more C++ but gives SIGSEV
    //Glib::ustring date_formated_s = right_now.format("%F %R:%S");
    
    g_print("%s:%d - ", date_formated, right_now.get_microsecond());
    g_free(date_formated);
}
