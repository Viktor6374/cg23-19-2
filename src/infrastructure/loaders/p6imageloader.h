#ifndef P6IMAGELOADER_H
#define P6IMAGELOADER_H

#include "imageloader.h"

class P6ImageLoader : public ImageLoader
{
public:
    P6ImageLoader();

    virtual Image *load(std::ifstream &in) override;
};

#endif // P6IMAGELOADER_H
