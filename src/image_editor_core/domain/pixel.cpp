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

int Pixel::get_red()
{
    return _red;
}

int Pixel::get_green()
{
    return _green;
}

int Pixel::get_blue()
{
    return _blue;
}
