#ifndef FROMHSV_TORGB_CONVERTER_H
#define FROMHSV_TORGB_CONVERTER_H

#include "torgb_converter.h"

class FromHSV_ToRGB_Converter : public ToRGB_Converter
{
public:
    FromHSV_ToRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // FROMHSV_TORGB_CONVERTER_H
