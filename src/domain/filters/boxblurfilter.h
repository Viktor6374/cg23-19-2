#ifndef BOXBLURFILTER_H
#define BOXBLURFILTER_H

#include "imagefilter.h"

class BoxBlurFilter : public ImageFilter
{
public:
    BoxBlurFilter(float radius);

    void execute(Image *image) override;

private:
    float _radius;
};

#endif // BOXBLURFILTER_H
