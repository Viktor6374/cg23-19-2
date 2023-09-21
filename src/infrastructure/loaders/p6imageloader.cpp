#include "p6imageloader.h"
#include <iostream>

P6ImageLoader::P6ImageLoader()
{
}

Image *P6ImageLoader::load(std::ifstream &in)
{
    int w;
    int h;
    in >> w >> h;
    int chislo;
    in >> chislo;
    std::vector<Pixel> vec;
    char red;
    char green;
    char blue;
    while (in.read(&blue, 1)){
        in.read(&red, 1);
        in.read(&green, 1);
        Pixel point(red, green, blue);
        vec.push_back(point);
    }
    if (vec.size() - 1 != w * h){
        throw std::exception();
    }
    return new Image(w, h, vec);
}
