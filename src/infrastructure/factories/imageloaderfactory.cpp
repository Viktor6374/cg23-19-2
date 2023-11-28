#include "imageloaderfactory.h"
#include "../loaders/p5imageloader.h"
#include "../loaders/p6imageloader.h"
#include "../loaders/pngimageloader.h"
#include <stdexcept>

ImageLoaderFactory::ImageLoaderFactory()
{
}

ImageLoader *ImageLoaderFactory::create(std::string image_type)
{
    if (image_type == "P5")
    {
        return new P5ImageLoader();
    }
    else if (image_type == "P6")
    {
        return new P6ImageLoader();
    }
    else if (image_type == "\x89\x50\x4E\x47")
    {
        return new PNGImageLoader();
    }
    else
    {
        throw std::logic_error("Unsupported or non-existent file");
    }
}
