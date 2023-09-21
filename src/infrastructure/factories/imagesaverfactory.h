#ifndef IMAGESAVERFACTORY_H
#define IMAGESAVERFACTORY_H

#include "../savers/imagesaver.h"
#include <string>

class ImageSaverFactory
{
public:
    ImageSaverFactory();

    ImageSaver *create(std::string image_type);
};

#endif // IMAGESAVERFACTORY_H
