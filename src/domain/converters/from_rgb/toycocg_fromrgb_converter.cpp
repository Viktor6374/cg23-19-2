#include "toycocg_fromrgb_converter.h"

ToYCoCg_FromRGB_Converter::ToYCoCg_FromRGB_Converter()
{
}

void ToYCoCg_FromRGB_Pixel_Converter(float* channels) {
    float R = channels[0];
    float G = channels[1];
    float B = channels[2];

    channels[0] = R / 4 + G / 2 + B / 4;
    channels[1] = R / 2 - B / 2 + 0.5;
    channels[2] = -R / 4 + G / 2 - B / 4 + 0.5;
}

void ToYCoCg_FromRGB_Converter::convert(Image *image)
{
    for (auto &pixel : image->pixels()) {
        ToYCoCg_FromRGB_Pixel_Converter(pixel.channels);
    }
}
