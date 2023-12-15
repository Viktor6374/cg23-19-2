#include "unsharpmaskingfilter.h"

UnsharpMaskingFilter::UnsharpMaskingFilter(float amount, float radius, unsigned char treshold)
{
    _amount = amount;
    _radius = radius;
    _treshold = treshold;
}

void UnsharpMaskingFilter::execute(Image *image)
{

}
