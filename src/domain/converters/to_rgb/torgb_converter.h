#ifndef TORGBCONVERTER_H
#define TORGBCONVERTER_H

#include "../../entities/image.h"

class ToRGB_Converter
{
public:
    ToRGB_Converter();
    virtual ~ToRGB_Converter();

    virtual void convert(Image *image) = 0;
};

#endif // TORGBCONVERTER_H
