#ifndef IMAGESAVER_H
#define IMAGESAVER_H

#include "../../domain/entities/image.h"
#include <fstream>

class ImageSaver
{
public:
    ImageSaver();
    virtual ~ImageSaver();

    virtual void save(Image *image, std::ofstream& out) = 0;
};

#endif // IMAGESAVER_H
