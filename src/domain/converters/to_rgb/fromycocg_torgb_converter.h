#ifndef FROMYCOCG_TORGB_CONVERTER_H
#define FROMYCOCG_TORGB_CONVERTER_H

#include "torgb_converter.h"

class FromYCoCg_ToRGB_Converter : public ToRGB_Converter
{
public:
    FromYCoCg_ToRGB_Converter();

    virtual void convert(Image* image) override;
};

#endif // FROMYCOCG_TORGB_CONVERTER_H
