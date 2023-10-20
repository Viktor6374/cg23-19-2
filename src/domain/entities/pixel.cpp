#include "pixel.h"

Pixel::Pixel()
{
    for (int i = 0; i < 3; ++i)
    {
        this->channels[i] = 0;
    }
}

Pixel::Pixel(float channel_1, float channel_2, float channel_3)
{
    this->channels[0] = channel_1;
    this->channels[1] = channel_2;
    this->channels[2] = channel_3;
}
