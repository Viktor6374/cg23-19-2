#include "fromycbcr601_torgb_converter.h"

FromYCbCr601_ToRGB_Converter::FromYCbCr601_ToRGB_Converter()
{
}

void FromYCbCr601_ToRGB_Pixel_Converter(float* channels) {
    float Y = channels[0];
    float Pb = channels[1] - 0.5;
    float Pr = channels[2] - 0.5;

    channels[0] = Y + Pr * 1.402;
    channels[1] = Y - Pb * 0.334136 - Pr * 0.714136;
    channels[2] = Y + Pb * 1.772;
}

void FromYCbCr601_ToRGB_Converter::convert(Image *image)
{
    for (auto pixel : image->pixels()) {
        FromYCbCr601_ToRGB_Pixel_Converter(pixel.channels);
    }
}
