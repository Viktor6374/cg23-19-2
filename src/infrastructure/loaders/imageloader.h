#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "../../domain/entities/image.h"
#include "../../domain/entities/bytepixel.h"
#include <fstream>

class ImageLoader
{
public:
    ImageLoader();
    virtual ~ImageLoader();

    virtual Image<BytePixel> *load(std::ifstream& in) = 0;
};

#endif // IMAGELOADER_H
