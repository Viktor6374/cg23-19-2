#include "pixel.h"

Pixel::Pixel()
{
    _red = 0;
    _green = 0;
    _blue = 0;
}

Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue)
{
    _red = red;
    _green = green;
    _blue = blue;
}

unsigned char Pixel::red() const
{
    return _red;
}

unsigned char Pixel::green() const
{
    return _green;
}

unsigned char Pixel::blue() const
{
    return _blue;
}
