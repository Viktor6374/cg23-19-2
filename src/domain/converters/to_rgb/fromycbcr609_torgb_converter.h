#ifndef FROMYCBCR609_TORGB_CONVERTER_H
#define FROMYCBCR609_TORGB_CONVERTER_H

#include "torgb_converter.h"

class FromYCbCr609_ToRGB_Converter : public ToRGB_Converter
{
public:
    FromYCbCr609_ToRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // FROMYCBCR609_TORGB_CONVERTER_H
