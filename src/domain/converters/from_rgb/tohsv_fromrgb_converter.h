#ifndef TOHSV_FROMRGB_CONVERTER_H
#define TOHSV_FROMRGB_CONVERTER_H

#include "fromrgb_converter.h"

class ToHSV_FromRGB_Converter : public FromRGB_Converter
{
public:
    ToHSV_FromRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // TOHSV_FROMRGB_CONVERTER_H
