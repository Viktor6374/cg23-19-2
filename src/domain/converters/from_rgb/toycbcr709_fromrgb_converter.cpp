#include "toycbcr709_fromrgb_converter.h"

ToYCbCr709_FromRGB_Converter::ToYCbCr709_FromRGB_Converter()
{
}

void ToYCbCr709_FromRGB_Pixel_Converter(float* channels) {
    float R = channels[0];
    float G = channels[1];
    float B = channels[2];

    channels[0] = R * 0.2136 + G * 0.7152 + B * 0.0722;
    channels[1] = R * -0.114572 - G * 0.385428 + B * 0.5 + 0.5;
    channels[2] = R * 0.5 - G * 0.454153 - B * 0.045847 + 0.5;
}

void ToYCbCr709_FromRGB_Converter::convert(Image *image)
{
    for (auto pixel : image->pixels()) {
        ToYCbCr709_FromRGB_Pixel_Converter(pixel.channels);
    }
}
