#include "image.h"

Image::Image()
{
    _width = 0;
    _height = 0;

    _pixels = std::vector<Pixel>();
}

Image::Image(int width, int height, std::vector<Pixel> pixels)
{
    _width = width;
    _height = height;

    _pixels = pixels;
}

int Image::get_width()
{
    return _width;
}

int Image::get_height()
{
    return _height;
}

const std::vector<Pixel>& Image::get_pixels()
{
    return _pixels;
}

Pixel Image::get_pixel_at(int x, int y)
{
    return _pixels[x + y * _width];
}
