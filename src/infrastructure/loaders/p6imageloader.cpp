#include "p6imageloader.h"
#include <iostream>

P6ImageLoader::P6ImageLoader()
{
}

Image<BytePixel> *P6ImageLoader::load(std::ifstream &in)
{
    int width, height;
    in >> width >> height;

    int max_color_value;
    in >> max_color_value;

    std::vector<BytePixel> pixels;
    char colors[3];

    in.read(colors, 1);

    while (in.read(colors, 3))
    {
        pixels.push_back(BytePixel(colors[0], colors[1], colors[2]));
    }

    return new Image(width, height, pixels);
}
