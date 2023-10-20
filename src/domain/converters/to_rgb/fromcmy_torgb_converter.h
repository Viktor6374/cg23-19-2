#ifndef FROMCMY_TORGB_CONVERTER_H
#define FROMCMY_TORGB_CONVERTER_H

#include "torgb_converter.h"

class FromCMY_ToRGB_Converter : public ToRGB_Converter
{
public:
    FromCMY_ToRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // FROMCMY_TORGB_CONVERTER_H
