#ifndef TOHSL_FROMRGB_CONVERTER_H
#define TOHSL_FROMRGB_CONVERTER_H

#include "fromrgb_converter.h"

class ToHSL_FromRGB_Converter : public FromRGB_Converter
{
public:
    ToHSL_FromRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // TOHSL_FROMRGB_CONVERTER_H
