#include "p5imageloader.h"
#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
#include<stdexcept>

P5ImageLoader::P5ImageLoader()
{
}

Image *P5ImageLoader::load(std::ifstream &in)
{
    int width, height;
    in >> width >> height;

    int max_color_value;
    in >> max_color_value;

    std::vector<BytePixel> pixels;
    char color;

    in.read(&color, 1);

    while (in.read(&color, 1))
    {
        pixels.push_back(BytePixel(color, color, color));
    }

    return new Image(width, height, pixels);
}
