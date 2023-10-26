#include "IconsRendererFactory.h"
#include "AlwaysSameIconProvider.h"
#include "../settings/Settings.h"
#include "FileAndDirectoryStaticIconProvider.h"
#include "FileByTypeIconProvider.h"

std::unique_ptr<FileIconProvider> IconsRendererFactory::createFromSettings() {
    return createForType(Settings::iconsRenderingType);
}

std::unique_ptr<FileIconProvider> IconsRendererFactory::createForType(FileIconsRenderingType fileIconsRenderingType) {
    switch (fileIconsRenderingType) {
        case ALWAYS_SAME_ICON:
            return std::make_unique<AlwaysSameIconProvider>();
        case FILE_AND_DIR_DISTINCT_ICON:
            return std::make_unique<FileAndDirectoryStaticIconProvider>();
        case FILE_TYPE_PER_ICON:
            return std::make_unique<FileByTypeIconProvider>();
        default:
            return std::make_unique<FileAndDirectoryStaticIconProvider>();
    }
}
