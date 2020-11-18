
#ifndef SIZE_FORMATTER_HR_H
#define SIZE_FORMATTER_HR_H

#include "SizeFormatter.h"
#include <memory>

/**
 * Human readable size formatter. Generated values like 23,45MB
 */
class SizeFormatterHr : public SizeFormatter, public std::shared_ptr<::SizeFormatter> {

public:
    virtual std::string formatSize(size_t bytes) const override;
};


#endif //SIZE_FORMATTER_HR_H
