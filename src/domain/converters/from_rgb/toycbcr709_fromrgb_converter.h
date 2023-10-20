#ifndef TOYCBCR709_FROMRGB_CONVERTER_H
#define TOYCBCR709_FROMRGB_CONVERTER_H

#include "fromrgb_converter.h"

class ToYCbCr709_FromRGB_Converter : public FromRGB_Converter
{
public:
    ToYCbCr709_FromRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // TOYCBCR709_FROMRGB_CONVERTER_H
