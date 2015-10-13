#include "SizeFormatterFactory.h"
#include "SizeFormatterHr.h"
#include "Settings.h"
#include "SizeFormatterSimple.h"
#include "SizeFormatterSpaces.h"

/**
 * Creates size formatter based on string read from configuration file
 */
std::shared_ptr<SizeFormatter> SizeFormatterFactory::createFromString(std::string inString) {
    std::shared_ptr<SizeFormatter> calculated = std::make_shared<SizeFormatterSimple>();
    if (inString == "HUMAN_READABLE") {
        calculated = std::make_shared<SizeFormatterHr>();
    } else if (inString == "SPACE_SEPARATED") {
        calculated = std::make_shared<SizeFormatterSpaces>();
    }
    return calculated;
}

std::shared_ptr<SizeFormatter> SizeFormatterFactory::createFromConfig() {
    Settings settings;
    std::string sizeFormatFromConfig = settings.readSizeFormat();
    return SizeFormatterFactory::createFromString(sizeFormatFromConfig);
}