#ifndef SIZE_FORMATTER_H
#define SIZE_FORMATTER_H

#include <bits/stringfwd.h>
#include "SizeDisplayFormat.h"

/**
 * Format size from bytes to given format
 */
class SizeFormatter {

public:
    static std::string formatSize(unsigned long bytes, SizeDisplayFormat format);
};

#endif //SIZE_FORMATTER_H
