#ifndef FROMRGBCONVERTERFACTORY_H
#define FROMRGBCONVERTERFACTORY_H

#include "../from_rgb/fromrgb_converter.h"
#include "../../models/colorspace.h"

class FromRGB_ConverterFactory
{
public:
    FromRGB_ConverterFactory();

    FromRGB_Converter *create(ColorSpace to);
};

#endif // FROMRGBCONVERTERFACTORY_H
