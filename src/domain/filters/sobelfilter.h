#ifndef SOBELFILTER_H
#define SOBELFILTER_H

#include "imagefilter.h"

class SobelFilter : public ImageFilter
{
public:
    SobelFilter();

    void execute(Image *image) override;
};

#endif // SOBELFILTER_H
