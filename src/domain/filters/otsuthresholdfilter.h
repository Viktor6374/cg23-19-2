#ifndef OTSUTHRESHOLDFILTER_H
#define OTSUTHRESHOLDFILTER_H

#include "imagefilter.h"

class OtsuThresholdFilter : public ImageFilter
{
public:
    OtsuThresholdFilter();

    void execute(Image *image) override;
};

#endif // OTSUTHRESHOLDFILTER_H
