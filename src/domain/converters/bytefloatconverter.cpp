#include "bytefloatconverter.h"

ByteFloatConverter::ByteFloatConverter()
{
}

Image<FloatPixel> *ByteFloatConverter::convert(Image<BytePixel> *image) {
    std::vector<FloatPixel> floatPixels;

    for (BytePixel bytePixel : image->pixels()) {
        float i1 = (float)bytePixel.channel_1 / 255;
        float i2 = (float)bytePixel.channel_2 / 255;
        float i3 = (float)bytePixel.channel_3 / 255;
        FloatPixel floatPixel = FloatPixel(i1, i2, i3);
        floatPixels.push_back(floatPixel);
    }

    return new Image<FloatPixel>(image->width(), image->height(), floatPixels);
}

Image<BytePixel> *ByteFloatConverter::convert(Image<FloatPixel> *image) {
    std::vector<BytePixel> bytePixels;

    for (FloatPixel floatPixel : image->pixels()) {
        unsigned char i1 = (unsigned char)floatPixel.channel_1 * 255;
        unsigned char i2 = (unsigned char)floatPixel.channel_2 * 255;
        unsigned char i3 = (unsigned char)floatPixel.channel_3 * 255;
        BytePixel bytePixel = BytePixel(i1, i2, i3);
        bytePixels.push_back(bytePixel);
    }

    return new Image<BytePixel>(image->width(), image->height(), bytePixels);
}
