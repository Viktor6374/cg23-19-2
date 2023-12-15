#ifndef UNSHARPMASKINGFILTER_H
#define UNSHARPMASKINGFILTER_H

#include "imagefilter.h"

class UnsharpMaskingFilter : public ImageFilter
{
public:
    UnsharpMaskingFilter(float amount, float radius, unsigned char treshold);

    void execute(Image *image) override;

private:
    float _amount;
    float _radius;
    unsigned char _treshold;
};

#endif // UNSHARPMASKINGFILTER_H
