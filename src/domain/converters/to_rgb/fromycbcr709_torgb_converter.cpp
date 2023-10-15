#include "fromycbcr709_torgb_converter.h"

FromYCbCr709_ToRGB_Converter::FromYCbCr709_ToRGB_Converter()
{
}

void FromYCbCr709_ToRGB_Pixel_Converter(float* channels) {
    float Y = channels[0];
    float Pb = channels[1] - 0.5;
    float Pr = channels[2] - 0.5;

    channels[0] = Y + Pr * 1.5748;
    channels[1] = Y - Pb * 0.187324 - Pr * 0.468124;
    channels[2] = Y + Pb * 1.8556;
}

void FromYCbCr709_ToRGB_Converter::convert(Image *image)
{
    for (auto pixel : image->pixels()) {
        FromYCbCr709_ToRGB_Pixel_Converter(pixel.channels);
    }
}
