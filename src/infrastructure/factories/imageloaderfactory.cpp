#include "imageloaderfactory.h"
#include "../loaders/p5imageloader.h"
#include "../loaders/p6imageloader.h"


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
    else
    {
        return nullptr;
    }
}
