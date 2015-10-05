#include "Preconditions.h"
#include <stdexcept>
#include <glibmm/ustring.h>

void Preconditions::checkArgument(bool shouldBeTrue, const Glib::ustring &errorMsg) {
    if (!shouldBeTrue) {
        throw std::runtime_error(errorMsg);
    }
}