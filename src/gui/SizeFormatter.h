#ifndef SIZE_FORMATTER_H
#define SIZE_FORMATTER_H

#include <string>

/**
 * Format size from bytes to given format
 */
class SizeFormatter {
public:
    virtual std::string formatSize(size_t bytes) const = 0;
};

#endif //SIZE_FORMATTER_H
