#include "tohsl_fromrgb_converter.h"
#include <cmath>

ToHSL_FromRGB_Converter::ToHSL_FromRGB_Converter()
{
}

void convert_channels_toHSL_fromRGB(float *channels)
{
    float R = channels[0];
    float G = channels[1];
    float B = channels[2];

    float Cmax = fmaxf(R, fmaxf(G, B));
    float Cmin = fminf(R, fminf(G, B));
    float delta = Cmax - Cmin;

    channels[2] = (Cmax + Cmin) / 2.0;

    if (delta == 0.0)
    {
        channels[1] = 0;
    }
    else
    {
        channels[1] = delta / (1 - fabsf(2 * channels[2] - 1));
    }

    if (delta == 0.0)
    {
        channels[0] = 0;
    }
    else if (delta == R)
    {
        channels[0] = 60 / 360.0 * (fmodf((G - B) / delta, 6));
    }
    else if (delta == G)
    {
        channels[0] = 60 / 360.0 * ((B - R) / delta + 2);
    }
    else if (delta == B)
    {
        channels[0] = 60 / 360.0 * ((R - G) / delta + 4);
    }
}

void ToHSL_FromRGB_Converter::convert(Image *image)
{
    for (auto pixel : image->pixels())
        convert_channels_toHSL_fromRGB(pixel.channels);
}
