#ifndef IMAGESAVER_H
#define IMAGESAVER_H

#include "../../domain/entities/image.h"
#include "../../domain/entities/bytepixel.h"
#include <fstream>

class ImageSaver
{
public:
    ImageSaver();
    virtual ~ImageSaver();

    virtual void save(Image<BytePixel> *image, std::ofstream& out) = 0;
};

#endif // IMAGESAVER_H
