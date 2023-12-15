#ifndef CANNYEDGEDETECTORFILTER_H
#define CANNYEDGEDETECTORFILTER_H

#include "imagefilter.h"

class CannyEdgeDetectorFilter : public ImageFilter
{
public:
    CannyEdgeDetectorFilter();

    void execute(Image *image) override;
};

#endif // CANNYEDGEDETECTORFILTER_H
