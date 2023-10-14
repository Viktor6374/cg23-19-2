#ifndef FROMYCBCR601_TORGB_CONVERTER_H
#define FROMYCBCR601_TORGB_CONVERTER_H

#include "torgb_converter.h"

class FromYCbCr601_ToRGB_Converter : public ToRGB_Converter
{
public:
    FromYCbCr601_ToRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // FROMYCBCR601_TORGB_CONVERTER_H
