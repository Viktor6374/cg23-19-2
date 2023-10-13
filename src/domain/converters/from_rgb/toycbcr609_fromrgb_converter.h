#ifndef TOYCBCR609_FROMRGB_CONVERTER_H
#define TOYCBCR609_FROMRGB_CONVERTER_H

#include "fromrgb_converter.h"

class ToYCbCr609_FromRGB_Converter : public FromRGB_Converter
{
public:
    ToYCbCr609_FromRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // TOYCBCR609_FROMRGB_CONVERTER_H
