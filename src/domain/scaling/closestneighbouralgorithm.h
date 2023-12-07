#ifndef CLOSESTNEIGHBOURALGORITHM_H
#define CLOSESTNEIGHBOURALGORITHM_H

#include "scalingalgorithm.h"

class ClosestNeighbourAlgorithm : public ScalingAlgorithm
{
public:
    ClosestNeighbourAlgorithm();

    Image *execute(Image *image, int new_width, int new_height, Point shift) override;
};

#endif // CLOSESTNEIGHBOURALGORITHM_H
