#include "fromcmy_torgb_converter.h"

FromCMY_ToRGB_Converter::FromCMY_ToRGB_Converter()
{
}

void FromCMY_ToRGB_Pixel_Converter(float* channels) {
    channels[0] = 1 - channels[0];
    channels[1] = 1 - channels[1];
    channels[2] = 1 - channels[2];
}

void FromCMY_ToRGB_Converter::convert(Image *image)
{
    for (auto &pixel : image->pixels()) {
        FromCMY_ToRGB_Pixel_Converter(pixel.channels);
    }
}
