#ifndef IMAGELOADERFACTORY_H
#define IMAGELOADERFACTORY_H


#include "../loaders/imageloader.h"
#include <string>

class ImageLoaderFactory
{
public:
    ImageLoaderFactory();

    ImageLoader* create(std::string image_type);
};

#endif // IMAGELOADERFACTORY_H
