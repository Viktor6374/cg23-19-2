#include "floatpixel.h"

FloatPixel::FloatPixel()
    : Pixel(0, 0, 0)
{
}

FloatPixel::FloatPixel(float channel_1, float channel_2, float channel_3)
    : Pixel(channel_1, channel_2, channel_3)
{
}
