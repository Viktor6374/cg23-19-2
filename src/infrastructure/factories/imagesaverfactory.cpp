#include "imagesaverfactory.h"
#include "../savers/p5imagesaver.h"
#include "../savers/p6imagesaver.h"
#include <stdexcept>

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
        throw std::logic_error("Unsupported file type");
    }
}
