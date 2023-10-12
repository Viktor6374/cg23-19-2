#ifndef BYTEFLOATCONVERTER_H
#define BYTEFLOATCONVERTER_H

#include "../entities/image.h"
#include "../entities/bytepixel.h"
#include "../entities/floatpixel.h"


class ByteFloatConverter
{
public:
    ByteFloatConverter();

    Image<FloatPixel> *convert(Image<BytePixel> *image);
    Image<BytePixel> *convert(Image<FloatPixel> *image);
};

#endif // BYTEFLOATCONVERTER_H
