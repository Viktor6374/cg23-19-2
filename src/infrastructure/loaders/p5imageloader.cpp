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

    std::vector<Pixel> pixels;
    char color;

    while (in.read(&color, 1))
    {
        pixels.push_back(Pixel(color, color, color));
    }

    if (pixels.size() == width * height + 1)
    {
        pixels.pop_back();
    }

    return new Image(width, height, pixels);
}
