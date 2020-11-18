#include "SizeFormatterSimple.h"
#include <sstream>

std::string SizeFormatterSimple::formatSize(size_t bytes) const {
    std::stringstream strStream;
    strStream << bytes;
    return strStream.str();
}