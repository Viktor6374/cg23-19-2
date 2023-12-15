#ifndef GAUSSFILTER_H
#define GAUSSFILTER_H

#include "imagefilter.h"

class GaussFilter : public ImageFilter
{
public:
    GaussFilter(float arg);

    void execute(Image *image) override;

private:
    float _arg;
};

#endif // GAUSSFILTER_H
