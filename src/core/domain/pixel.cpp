#include "pixel.h"

Pixel::Pixel()
{
    _red = 0;
    _green = 0;
    _blue = 0;
}

Pixel::Pixel(int red, int green, int blue)
{
    _red = red;
    _green = green;
    _blue = blue;
}

int Pixel::red()
{
    return _red;
}

int Pixel::green()
{
    return _green;
}

int Pixel::blue()
{
    return _blue;
}
