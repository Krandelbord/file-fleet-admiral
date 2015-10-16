#include "SizeFormatterHr.h"
#include <vector>

/* bytes, kilobytes, megabytes, gigabytes, terabytes, petabytes, exabytes,
  * zettabytes, yottabytes.
  */
const std::string HW[] = {"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
std::vector<std::string> const UnitTypes(std::begin(HW), std::end(HW));

/**
 * Format size into human readable format
 */
std::string SizeFormatterHr::formatSize(size_t sizeInBytes) const {

    char printBuffer[300];
    double sizeDividedByUnit;
    if (sizeInBytes >= 0) {
        sizeDividedByUnit = sizeInBytes;
    } else {
        sizeDividedByUnit = -1 * sizeInBytes;
    }

    unsigned int unitIndex = 0;
    while (unitIndex <= UnitTypes.size()) {
        if (sizeDividedByUnit < 100 && unitIndex != 0) {
            snprintf(printBuffer, sizeof(printBuffer), "%.2f %s", sizeDividedByUnit, UnitTypes[unitIndex].c_str());
            break;
        }

        if (sizeDividedByUnit < 1000) {
            //print size in bytes
            snprintf(printBuffer, sizeof(printBuffer), "%.0f %s", sizeDividedByUnit, UnitTypes[unitIndex].c_str());
            break;
        }
        sizeDividedByUnit /= 1024.0;
        unitIndex++;
    }
    return std::string(printBuffer);
}
