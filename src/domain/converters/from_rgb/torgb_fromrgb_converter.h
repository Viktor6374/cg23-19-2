#ifndef TORGBFROMRGBCONVERTER_H
#define TORGBFROMRGBCONVERTER_H

#include "fromrgb_converter.h"

class ToRGB_FromRGB_Converter : public FromRGB_Converter
{
public:
    ToRGB_FromRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // TORGBFROMRGBCONVERTER_H
