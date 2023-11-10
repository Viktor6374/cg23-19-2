#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include "../../domain/entities/image.h"
#include "../../domain/factories/ditheringalgorithmfactory.h"
#include <QImage>

class ImageConverter
{
public:
    ImageConverter();
    ~ImageConverter();

    QImage *convert_to_QImage(Image *image, std::string dithering_type, int bytes_count);

private:
    DitheringAlgorithmFactory *_dithering_algorithm_factory;
};

#endif // IMAGECONVERTER_H
