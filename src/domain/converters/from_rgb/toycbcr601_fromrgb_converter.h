#ifndef TOYCBCR601_FROMRGB_CONVERTER_H
#define TOYCBCR601_FROMRGB_CONVERTER_H

#include "fromrgb_converter.h"

class ToYCbCr601_FromRGB_Converter : public FromRGB_Converter
{
public:
    ToYCbCr601_FromRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // TOYCBCR601_FROMRGB_CONVERTER_H
