#ifndef CONTRASTADAPTIVESHARPENINGFILTER_H
#define CONTRASTADAPTIVESHARPENINGFILTER_H

#include "imagefilter.h"

class ContrastAdaptiveSharpeningFilter : public ImageFilter
{
public:
    ContrastAdaptiveSharpeningFilter(float sharpness);

    void execute(Image *image) override;

private:
    float _sharpness;
};

#endif // CONTRASTADAPTIVESHARPENINGFILTER_H
