#ifndef IMAGESAVER_H
#define IMAGESAVER_H

#include "../../domain/entities/image.h"
#include "../../domain/factories/ditheringalgorithmfactory.h"
#include <fstream>

class ImageSaver
{
public:
    ImageSaver();
    virtual ~ImageSaver();

    virtual void save(Image *image, std::ofstream& out, std::string dithering_type, int bytes_count) = 0;

protected:
    DitheringAlgorithmFactory *_dithering_algorithm_factory;
};

#endif // IMAGESAVER_H
