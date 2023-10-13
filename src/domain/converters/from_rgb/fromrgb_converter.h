#ifndef FROMRGBCONVERTER_H
#define FROMRGBCONVERTER_H

#include "../../entities/image.h"

class FromRGB_Converter
{
public:
    FromRGB_Converter();
    virtual ~FromRGB_Converter();

    virtual void convert(Image* image) = 0;
};

#endif // FROMRGBCONVERTER_H
