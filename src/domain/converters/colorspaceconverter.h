#ifndef COLORSPACECONVERTER_H
#define COLORSPACECONVERTER_H

#include "../entities/image.h"
#include "../entities/floatpixel.h"
#include "../models/colorspace.h"

class ColorSpaceConverter
{
public:
    ColorSpaceConverter();

    void Convert(Image<FloatPixel>& image, ColorSpace from, ColorSpace to);
};

#endif // COLORSPACECONVERTER_H
