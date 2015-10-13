
#ifndef SIZE_FORMATTER_HR_H
#define SIZE_FORMATTER_HR_H

#include "SizeFormatter.h"

/**
 * Human readable size formater. Generated values like 23,45MB
 */
class SizeFormatterHr : public SizeFormatter {

public:
    virtual std::string formatSize(size_t bytes) override;
};


#endif //SIZE_FORMATTER_HR_H
