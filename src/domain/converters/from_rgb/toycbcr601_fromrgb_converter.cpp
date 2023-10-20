#include "toycbcr601_fromrgb_converter.h"

ToYCbCr601_FromRGB_Converter::ToYCbCr601_FromRGB_Converter()
{
}

void ToYCbCr601_FromRGB_Pixel_Converter(float* channels) {
    float R = channels[0];
    float G = channels[1];
    float B = channels[2];

    channels[0] = R * 0.299 + G * 0.587 + B * 0.114;
    channels[1] = R * -0.168736 - G * 0.331264 + B * 0.5 + 0.5;
    channels[2] = R * 0.5 - G * 0.418688 - B * 0.081312 + 0.5;
}

void ToYCbCr601_FromRGB_Converter::convert(Image *image)
{
    for (auto &pixel : image->pixels()) {
        ToYCbCr601_FromRGB_Pixel_Converter(pixel.channels);
    }
}
