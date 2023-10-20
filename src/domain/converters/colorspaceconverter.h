#ifndef COLORSPACECONVERTER_H
#define COLORSPACECONVERTER_H

#include "../entities/image.h"
#include "../models/colorspace.h"
#include "factories/torgb_converterfactory.h"
#include "factories/fromrgb_converterfactory.h"

class ColorSpaceConverter
{
public:
    ColorSpaceConverter();
    ~ColorSpaceConverter();

    void convert(Image *image, ColorSpace from, ColorSpace to);


private:
    ToRGB_ConverterFactory *_to_rgb_converter_factory;
    FromRGB_ConverterFactory *_from_rgb_converter_factory;
};

#endif // COLORSPACECONVERTER_H
