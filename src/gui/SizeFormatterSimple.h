#ifndef SIZE_FORMATTER_SIMPLE_H
#define SIZE_FORMATTER_SIMPLE_H

#include "SizeFormatter.h"
#include <memory>

/**
 * Simple formatter just numbers without unit for example output will be "233344"
 */
class SizeFormatterSimple : public SizeFormatter, public std::shared_ptr<::SizeFormatter> {
public:
    virtual std::string formatSize(size_t bytes) const override;
};
#endif //SIZE_FORMATTER_SIMPLE_H
