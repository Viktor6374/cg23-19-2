#include "imageconverter.h"
#include "../../domain/entities/floatpixel.h"

ImageConverter::ImageConverter()
{
}

QImage *ImageConverter::convert_to_QImage(Image<FloatPixel> *image)
{
    uchar *data = new uchar[image->pixels().size() * 3];

    for (int i = 0; i < image->pixels().size(); ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            unsigned char channel = (unsigned char)(image->pixels()[i].channels[j] * 255);

            data[3 * i + j] = channel;
        }
    }

    QImage *qImage = new QImage(data, image->width(), image->height(), QImage::Format_RGB888);

    return qImage;
}
