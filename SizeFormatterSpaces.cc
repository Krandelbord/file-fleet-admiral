#include "SizeFormatterSpaces.h"
#include <sstream>

std::string SizeFormatterSpaces::formatSize(size_t bytes) const {
    std::stringstream strStream;
    strStream << bytes;

    std::string string = strStream.str();
    size_t placeToPutSpace = string.length() - SPACE_SEPARATOR_EVERY;
    for (; placeToPutSpace < string.length() && placeToPutSpace > 0; placeToPutSpace+=(-SPACE_SEPARATOR_EVERY)) {
        string.insert(placeToPutSpace, " ");
    }
    return string;
}
