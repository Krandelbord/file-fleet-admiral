#ifndef SIZE_FORMATTER_FACTORY_H
#define SIZE_FORMATTER_FACTORY_H

#include "SizeFormatter.h"

class SizeFormatterFactory {
public:
    static std::shared_ptr<SizeFormatter> createFromString(std::string inString);
};


#endif //SIZE_FORMATTER_FACTORY_H
