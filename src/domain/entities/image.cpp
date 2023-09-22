#include "image.h"
#include <stdexcept>

Image::Image()
{
    _width = 0;
    _height = 0;

    _pixels = std::vector<Pixel>();
}

Image::Image(int width, int height, const std::vector<Pixel>& pixels)
{
    if (width <= 0)
        throw std::domain_error("Incorrect image width");

    if (height <= 0)
        throw std::domain_error("Incorrect image height");

    if (pixels.size() != width * height)
        throw std::domain_error("Incorrect image pixels count");

    _width = width;
    _height = height;

    _pixels = pixels;
}

int Image::width() const
{
    return _width;
}

int Image::height() const
{
    return _height;
}

const std::vector<Pixel>& Image::pixels() const
{
    return _pixels;
}

const Pixel& Image::pixel_at(int x, int y) const
{
    return _pixels.at(x + y * _width);
}
