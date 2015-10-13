#include "SizeFormatterFactory.h"
#include "SizeFormatterHr.h"

/**
 * Creates size formatter based on string read from configuration file
 */
std::shared_ptr<SizeFormatter> SizeFormatterFactory::createFromString(std::string inString) {
    std::shared_ptr<SizeFormatter> oneCreated = std::make_shared<SizeFormatterHr>();
    return oneCreated;
}