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
    int w;
    int h;
    in >> w >> h;
    int chislo;
    in >> chislo;
    std::vector<Pixel> vec;
    char color;
    while (in.read(&color, 1)){
        Pixel point(color, color, color);
        vec.push_back(point);
    }
    if (vec.size() != w * h){
        throw std::exception();
    }
    return new Image(w, h, vec);
}
