#ifndef SIZE_FORMATTER_SIMPLE_H
#define SIZE_FORMATTER_SIMPLE_H

#include "SizeFormatter.h"

class SizeFormatterSimple : public SizeFormatter {
public:
    std::string formatSize(size_t bytes);
};

#endif //SIZE_FORMATTER_SIMPLE_H
