#include "imageconverter.h"

ImageConverter::ImageConverter()
{
}

QImage *ImageConverter::convert_to_QImage(Image *image)
{
    uchar *data = new uchar[image->pixels().size() * 3];

    for (int i = 0; i < image->pixels().size(); ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            data[3 * i + j] = (uchar)image->pixels()[i].channels[j];
        }
    }

    QImage *qImage = new QImage(data, image->width(), image->height(), QImage::Format_RGB888);

    return qImage;
}
