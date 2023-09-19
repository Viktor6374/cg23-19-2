#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include "../domain/entities/image.h"
#include <QImage>

class ImageConverter
{
public:
    ImageConverter();

    QImage convert_to_QImage(Image image);
};

#endif // IMAGECONVERTER_H
