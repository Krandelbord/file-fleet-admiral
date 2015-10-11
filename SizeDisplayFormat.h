#ifndef SIZE_DISPLAY_FORMAT_H
#define SIZE_DISPLAY_FORMAT_H

#include <gtkmm.h>
/**
 * Possibilites how size of the files is displayed
 */
enum class SizeDisplayFormat {
    IN_BYTES,
    SPACE_SEPARATED,
    HR_ROUNDED,
    HR_FULL,
};

std::string convertSizeDFToString(SizeDisplayFormat toConvert);

#endif /** SIZE_DISPLAY_FORMAT_H */
