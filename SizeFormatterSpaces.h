#ifndef SIZE_FORMATTER_SPACES_H
#define SIZE_FORMATTER_SPACES_H


#include "SizeFormatter.h"

/**
 * Formats size putting spaces every 100-th unit
 */
class SizeFormatterSpaces : public SizeFormatter {
/** Space separator every 3 char **/
    static const int SPACE_SEPARATOR_EVERY = 3;

public:
    virtual std::string formatSize(size_t bytes) const override;
};


#endif //SIZE_FORMATTER_SPACES_H
