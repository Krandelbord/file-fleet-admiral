#ifndef GTKMM_FILE_MANAGER_PRECONDITIONS_H
#define GTKMM_FILE_MANAGER_PRECONDITIONS_H

#include <glibmm/ustring.h>

class Preconditions {
public:
    static void checkArgument(bool shouldBeTrue, const Glib::ustring& errorMsg);

};
#endif //GTKMM_FILE_MANAGER_PRECONDITIONS_H
