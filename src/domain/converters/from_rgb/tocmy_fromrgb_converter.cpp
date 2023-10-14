#include "tocmy_fromrgb_converter.h"

ToCMY_FromRGB_Converter::ToCMY_FromRGB_Converter()
{
}

void ToCMY_FromRGB_Pixel_Converter(float* channels) {
    channels[0] = 1 - channels[0];
    channels[1] = 1 - channels[1];
    channels[2] = 1 - channels[2];
}

void ToCMY_FromRGB_Converter::convert(Image *image)
{
    for (auto pixel : image->pixels()) {
        ToCMY_FromRGB_Pixel_Converter(pixel.channels);
    }
}
