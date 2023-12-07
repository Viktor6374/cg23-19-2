#ifndef BILINEARALGORITHM_H
#define BILINEARALGORITHM_H

#include "scalingalgorithm.h"

class BilinearAlgorithm : public ScalingAlgorithm
{
public:
    BilinearAlgorithm();

    Image *execute(Image *image, int new_width, int new_height, Point shift) override;

};

#endif // BILINEARALGORITHM_H
