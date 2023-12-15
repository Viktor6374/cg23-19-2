#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#include "../entities/image.h"

class ImageFilter
{
public:
    ImageFilter();
    virtual ~ImageFilter();

    virtual void execute(Image *image) = 0;
};

#endif // IMAGEFILTER_H
