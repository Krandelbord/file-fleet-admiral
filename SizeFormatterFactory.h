#ifndef SIZE_FORMATTER_FACTORY_H
#define SIZE_FORMATTER_FACTORY_H

#include "SizeFormatter.h"
#include <memory>

class SizeFormatterFactory {
public:
    static std::shared_ptr<SizeFormatter> createFromString(std::string inString);
    static std::shared_ptr<SizeFormatter> createFromConfig();
};


#endif //SIZE_FORMATTER_FACTORY_H
