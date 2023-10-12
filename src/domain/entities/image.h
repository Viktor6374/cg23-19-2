#ifndef IMAGE_H
#define IMAGE_H

#include "pixel.h"
#include <vector>

template<class TPixel>
class Image
{
public:
    Image();
    Image(int width, int height, const std::vector<TPixel>& pixels);

    int width() const;
    int height() const;

    std::vector<TPixel>& pixels();

private:
    int _width;
    int _height;

    std::vector<TPixel> _pixels;
};

#endif // IMAGE_H
