#ifndef FROMRGBTORGBCONVERTER_H
#define FROMRGBTORGBCONVERTER_H

#include "torgb_converter.h"

class FromRGB_ToRGB_Converter : public ToRGB_Converter
{
public:
    FromRGB_ToRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // FROMRGBTORGBCONVERTER_H
