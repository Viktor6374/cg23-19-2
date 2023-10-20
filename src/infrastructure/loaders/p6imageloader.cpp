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

    in.read(colors, 1);

    while (in.read(colors, 3))
    {
        pixels.push_back(Pixel(colors[0] / 255.0, colors[1] / 255.0, colors[2] / 255.0));
    }

    return new Image(width, height, pixels);
}
