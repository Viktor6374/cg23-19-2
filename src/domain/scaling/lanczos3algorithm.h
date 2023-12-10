#ifndef LANCZOS3ALGORITHM_H
#define LANCZOS3ALGORITHM_H

#include "scalingalgorithm.h"

class Lanczos3Algorithm : public ScalingAlgorithm
{
public:
    Lanczos3Algorithm();

    Image *execute(Image *image, int new_width, int new_height, Point shift) override;
};

#endif // LANCZOS3ALGORITHM_H
