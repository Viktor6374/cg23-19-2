#ifndef THRESHOLDFILTER_H
#define THRESHOLDFILTER_H

#include "imagefilter.h"

class ThresholdFilter : public ImageFilter
{
public:
    ThresholdFilter(unsigned char border1, unsigned char border2);

    void execute(Image *image) override;

private:
    unsigned char _border1;
    unsigned char _border2;
};

#endif // THRESHOLDFILTER_H
