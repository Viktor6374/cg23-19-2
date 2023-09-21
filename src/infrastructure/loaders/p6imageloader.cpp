#include "p6imageloader.h"

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
    while (in.read(&red, 1)){
        in.read(&green, 1);
        in.read(&blue, 1);
        Pixel point(red, green, blue);
        vec.push_back(point);
    }
    if (vec.size() != w * h){
        throw std::exception();
    }
    return new Image(w, h, vec);
}
