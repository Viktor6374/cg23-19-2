#include "imagesaverfactory.h"
#include "../savers/p5imagesaver.h"
#include "../savers/p6imagesaver.h"

ImageSaverFactory::ImageSaverFactory()
{
}

ImageSaver *ImageSaverFactory::create(std::string image_type)
{
    if (image_type == "P5")
    {
        return new P5ImageSaver();
    }
    else if (image_type == "P6")
    {
        return new P6ImageSaver();
    }
    else
    {
        return nullptr;
    }
}
