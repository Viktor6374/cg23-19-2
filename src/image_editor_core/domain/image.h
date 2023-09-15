#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "pixel.h"

class Image
{
public:
    Image();
    Image(int width, int height, std::vector<Pixel> pixels);

    int get_width();
    int get_height();

    const std::vector<Pixel>& get_pixels();

    Pixel get_pixel_at(int x, int y);

private:
    int _width;
    int _height;

    std::vector<Pixel> _pixels;
};

#endif // IMAGE_H
