#ifndef SIZE_FORMATTER_H
#define SIZE_FORMATTER_H

#include "SizeDisplayFormat.h"

/**
 * Format size from bytes to given format
 */
class SizeFormatter {
public:
    virtual std::string formatSize(size_t bytes) = 0;
};

#endif //SIZE_FORMATTER_H
