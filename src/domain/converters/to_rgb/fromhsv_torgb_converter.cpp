#include "fromhsv_torgb_converter.h"
#include <cmath>

FromHSV_ToRGB_Converter::FromHSV_ToRGB_Converter()
{
}

void convert_channels(float *channels)
{
    float H = channels[0];
    float S = channels[1];
    float V = channels[2];

    float C = V * S;
    float X = C * (1 - std::abs(fmodf(H / 60 * 360.0, 2) - 1));
    float m = V - C;

    if (H < 60 / 360.0)
    {
        channels[0] = C + m;
        channels[1] = X + m;
        channels[2] = m;
    }
    else if (H < 120 / 360.0)
    {
        channels[0] = X + m;
        channels[1] = C + m;
        channels[2] = m;
    }
    else if (H < 180 / 360.0)
    {
        channels[0] = m;
        channels[1] = C + m;
        channels[2] = X + m;
    }
    else if (H < 240 / 360.0)
    {
        channels[0] = m;
        channels[1] = X + m;
        channels[2] = C + m;
    }
    else if (H < 300 / 360.0)
    {
        channels[0] = X + m;
        channels[1] = m;
        channels[2] = C + m;
    }
    else
    {
        channels[0] = C + m;
        channels[1] = m;
        channels[2] = X + m;
    }
}

void FromHSV_ToRGB_Converter::convert(Image *image)
{
    for (auto &pixel : image->pixels())
        convert_channels(pixel.channels);
}
