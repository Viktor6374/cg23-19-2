#include "p6imageloader.h"
#include <iostream>

P6ImageLoader::P6ImageLoader()
{
}

Image *P6ImageLoader::load(std::ifstream &in)
{
    int width, height;
    in >> width >> height;

    int max_color_value;
    in >> max_color_value;

    std::vector<Pixel> pixels;
    char colors[3];

    while (in.read(colors, 3))
    {
        pixels.push_back(Pixel(colors[1], colors[2], colors[0]));
    }

    return new Image(width, height, pixels);
}
