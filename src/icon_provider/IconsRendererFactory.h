
#ifndef FILE_FLEET_ADMIRAL_ICONSRENDERERFACTORY_H
#define FILE_FLEET_ADMIRAL_ICONSRENDERERFACTORY_H


#include "IconProvider.h"
#include "../settings/FileIconsRenderingType.h"
#include "FileIconProvider.h"

class IconsRendererFactory {
    static std::unique_ptr<FileIconProvider> createForType(FileIconsRenderingType fileIconsRenderingType);

public:
    static std::unique_ptr<FileIconProvider> createFromSettings();
};


#endif //FILE_FLEET_ADMIRAL_ICONSRENDERERFACTORY_H
