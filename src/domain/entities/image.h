#ifndef IMAGE_H
#define IMAGE_H

#include "pixel.h"
#include <vector>

class Image
{
public:
    Image();
    Image(int width, int height, const std::vector<Pixel>& pixels);

    int width() const;
    int height() const;

    std::vector<Pixel>& pixels();
    const std::vector<Pixel>& pixels() const;

    Pixel &pixel_at(int x, int y);
    const Pixel &pixel_at(int x, int y) const;

private:
    int _width;
    int _height;

    std::vector<Pixel> _pixels;
};

#endif // IMAGE_H
