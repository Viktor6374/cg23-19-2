#include "imageconverter.h"

ImageConverter::ImageConverter()
{
}

QImage *ImageConverter::convert_to_QImage(Image *image)
{
    uchar *data = (uchar *)image->pixels().data();
    QImage *_qImage = new QImage(data, image->width(), image->height(), QImage::Format_RGB888);
    return _qImage;
}
