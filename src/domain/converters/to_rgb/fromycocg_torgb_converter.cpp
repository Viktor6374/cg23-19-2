#include "fromycocg_torgb_converter.h"

FromYCoCg_ToRGB_Converter::FromYCoCg_ToRGB_Converter()
{
}

void FromYCoCg_ToRGB_Pixel_Converter(float* channels) {
    float Y = channels[0];
    float Co = channels[1];
    float Cg = channels[2];

    channels[0] = Y + Co - Cg;
    channels[1] = Y + Cg - 0.5;
    channels[2] = Y - Co - Cg + 1;
}

void FromYCoCg_ToRGB_Converter::convert(Image *image)
{
    for (auto &pixel : image->pixels()) {
        FromYCoCg_ToRGB_Pixel_Converter(pixel.channels);
    }
}
