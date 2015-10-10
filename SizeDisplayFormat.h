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

std::string convertSizeDFToString(SizeDisplayFormat toConvert) {
    switch (toConvert) {
        case SizeDisplayFormat::IN_BYTES:
            return "IN_BYTES";
        case SizeDisplayFormat::SPACE_SEPARATED:
            return "SPACE_SEPARATED";
        case SizeDisplayFormat::HR_ROUNDED:
            return "HR_ROUNDED";
        case SizeDisplayFormat::HR_FULL:
             return "HR_FULL";
    }
    throw std::runtime_error("invalid enum value ");
}
#endif /** SIZE_DISPLAY_FORMAT_H */
