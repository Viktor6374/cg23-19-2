#include "tohsv_fromrgb_converter.h"
#include <cmath>

ToHSV_FromRGB_Converter::ToHSV_FromRGB_Converter()
{
}

void convert_channels_toHSV_fromRGB(float *channels)
{
    float R = channels[0];
    float G = channels[1];
    float B = channels[2];

    float Cmax = fmaxf(R, fmaxf(G, B));
    float Cmin = fminf(R, fminf(G, B));
    float delta = Cmax - Cmin;

    channels[2] = Cmax;

    if (Cmax == 0)
    {
        channels[1] = 0;
    }
    else
    {
        channels[1] = delta / Cmax;
    }

    if (delta == 0)
    {
        channels[0] = 0;
    }
    else if (Cmax == R)
    {
        channels[0] = 60 / 360.0 * ((G - B) / delta);
    }
    else if (Cmax == G)
    {
        channels[0] = 60 / 360.0 * ((B - R) / delta + 2);
    }
    else if (Cmax == B)
    {
        channels[0] = 60 / 360.0 * ((R - G) / delta + 4);
    }

    if (channels[0] > 1){
        channels[0] = 1;
    }
    else if (channels[0] < 0) {
        channels[0] = 0;
    }
}

void ToHSV_FromRGB_Converter::convert(Image *image)
{
    for (auto &pixel : image->pixels())
        convert_channels_toHSV_fromRGB(pixel.channels);
}
