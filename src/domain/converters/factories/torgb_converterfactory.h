#ifndef TORGBCONVERTERFACTORY_H
#define TORGBCONVERTERFACTORY_H

#include "../to_rgb/torgb_converter.h"
#include "../../models/colorspace.h"

class ToRGB_ConverterFactory
{
public:
    ToRGB_ConverterFactory();

    ToRGB_Converter *create(ColorSpace from);
};

#endif // TORGBCONVERTERFACTORY_H
