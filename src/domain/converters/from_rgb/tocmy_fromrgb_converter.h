#ifndef TOCMY_FROMRGB_CONVERTER_H
#define TOCMY_FROMRGB_CONVERTER_H

#include "fromrgb_converter.h"

class ToCMY_FromRGB_Converter : public FromRGB_Converter
{
public:
    ToCMY_FromRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // TOCMY_FROMRGB_CONVERTER_H
