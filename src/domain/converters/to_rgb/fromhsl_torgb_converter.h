#ifndef FROMHSL_TORGB_CONVERTER_H
#define FROMHSL_TORGB_CONVERTER_H

#include "torgb_converter.h"

class FromHSL_ToRGB_Converter : public ToRGB_Converter
{
public:
    FromHSL_ToRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // FROMHSL_TORGB_CONVERTER_H
