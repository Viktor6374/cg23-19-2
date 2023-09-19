#ifndef P5IMAGELOADER_H
#define P5IMAGELOADER_H


#include "imageloader.h"

class P5ImageLoader : public ImageLoader
{
public:
    P5ImageLoader();

    virtual Image load(const std::ifstream &in) override;
};

#endif // P5IMAGELOADER_H
