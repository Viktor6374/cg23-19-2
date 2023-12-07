#ifndef SCALINGALGORITHM_H
#define SCALINGALGORITHM_H

#include "../entities/image.h"
#include "../models/point.h"

class ScalingAlgorithm
{
public:
    ScalingAlgorithm();
    virtual ~ScalingAlgorithm();

    virtual Image *execute(Image *image, int new_width, int new_height, Point shift) = 0;
};

#endif // SCALINGALGORITHM_H
