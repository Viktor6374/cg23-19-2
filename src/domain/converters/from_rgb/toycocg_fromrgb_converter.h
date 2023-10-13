#ifndef TOYCOCG_FROMRGB_CONVERTER_H
#define TOYCOCG_FROMRGB_CONVERTER_H

#include "fromrgb_converter.h"

class ToYCoCg_FromRGB_Converter : public FromRGB_Converter
{
public:
    ToYCoCg_FromRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // TOYCOCG_FROMRGB_CONVERTER_H
