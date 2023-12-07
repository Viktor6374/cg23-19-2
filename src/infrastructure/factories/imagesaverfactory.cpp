#include "imagesaverfactory.h"
#include "../savers/p5imagesaver.h"
#include "../savers/p6imagesaver.h"
#include "../savers/pngimagesaver.h"
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
    else if(image_type == "PNG Color")
    {
        return new pngimagesaver();
    }
    else if (image_type == "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A")
    {
        return nullptr;
    }
    else
    {
        throw std::logic_error("Unsupported or non-existent file");
    }
}
