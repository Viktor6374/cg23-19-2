#include "image.h"

Image::Image()
{
    _width = 0;
    _height = 0;

    _pixels = std::vector<Pixel>();
}

Image::Image(int width, int height, const std::vector<Pixel>& pixels)
{
    _width = width;
    _height = height;

    _pixels = pixels;
}

int Image::width()
{
    return _width;
}

int Image::height()
{
    return _height;
}

const std::vector<Pixel>& Image::pixels()
{
    return _pixels;
}

const Pixel& Image::pixel_at(int x, int y)
{
    return _pixels[x + y * _width];
}
