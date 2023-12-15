#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include "imagefilter.h"

class MedianFilter : public ImageFilter
{
public:
    MedianFilter(float radius);

    void execute(Image *image) override;

private:
    float _radius;
};

#endif // MEDIANFILTER_H
