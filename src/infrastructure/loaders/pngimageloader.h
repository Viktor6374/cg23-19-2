#ifndef PNGIMAGELOADER_H
#define PNGIMAGELOADER_H

#include "imageloader.h"

class PNGImageLoader : public ImageLoader
{
public:
    PNGImageLoader();
    Image *load(std::ifstream& in);
};

#endif // PNGIMAGELOADER_H
