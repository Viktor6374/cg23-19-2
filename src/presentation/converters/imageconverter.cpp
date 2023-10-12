#include "imageconverter.h"
#include "../../domain/entities/floatpixel.h"

ImageConverter::ImageConverter()
{
}

QImage *ImageConverter::convert_to_QImage(Image<FloatPixel> *image)
{
    uchar *data = (uchar *)image->pixels().data();

    QImage *qImage = new QImage(data, image->width(), image->height(), QImage::Format_RGB888);

    return qImage;
}
