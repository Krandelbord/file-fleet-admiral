#ifndef ASSERTS_H
#define ASSERTS_H

#include <glibmm.h>

class Asserts { 
    public:
          static bool assertEquals(const Glib::ustring& msgIfFails, const Glib::ustring& expected, const Glib::ustring& actual);
};
#endif /** ASSERTS_H */
