#include "imageconverter.h"
#include "../../domain/entities/floatpixel.h"

ImageConverter::ImageConverter()
{
    _dithering_algorithm_factory = new DitheringAlgorithmFactory();
}

ImageConverter::~ImageConverter()
{
    delete _dithering_algorithm_factory;
}

QImage *ImageConverter::convert_to_QImage(Image *image, std::string dithering_type, int bytes_count)
{
    auto algorithm = _dithering_algorithm_factory->create(dithering_type);
    unsigned char *data = algorithm->execute(image, bytes_count);

    QImage *qImage = new QImage(data, image->width(), image->height(), QImage::Format_RGB888);

    delete algorithm;

    return qImage;
}
