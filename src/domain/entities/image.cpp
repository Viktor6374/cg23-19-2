#include "image.h"
#include <stdexcept>

template<class TPixel>
Image<TPixel>::Image()
{
    _width = 0;
    _height = 0;

    _pixels = std::vector<TPixel>();
}

template<class TPixel>
Image<TPixel>::Image(int width, int height, const std::vector<TPixel>& pixels)
{
    if (width <= 0)
        throw std::logic_error("Incorrect image width");

    if (height <= 0)
        throw std::logic_error("Incorrect image height");

    if (pixels.size() != width * height)
        throw std::logic_error("Incorrect image pixels count");

    _width = width;
    _height = height;

    _pixels = pixels;
}

template<class TPixel>
int Image<TPixel>::width() const
{
    return _width;
}

template<class TPixel>
int Image<TPixel>::height() const
{
    return _height;
}

template<class TPixel>
std::vector<TPixel>& Image<TPixel>::pixels()
{
    return _pixels;
}
