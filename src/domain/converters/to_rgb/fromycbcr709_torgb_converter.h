#ifndef FROMYCBCR709_TORGB_CONVERTER_H
#define FROMYCBCR709_TORGB_CONVERTER_H

#include "torgb_converter.h"

class FromYCbCr709_ToRGB_Converter : public ToRGB_Converter
{
public:
    FromYCbCr709_ToRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // FROMYCBCR709_TORGB_CONVERTER_H
