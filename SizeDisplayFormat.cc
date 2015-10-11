
#include "SizeDisplayFormat.h"

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