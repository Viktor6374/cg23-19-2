#ifndef BCSPLINEALGORITHM_H
#define BCSPLINEALGORITHM_H

#include "scalingalgorithm.h"

class BCSplineAlgorithm : public ScalingAlgorithm
{
public:
    BCSplineAlgorithm(float b, float c);

    Image *execute(Image *image, int new_width, int new_height, Point shift) override;

private:
    float _b;
    float _c;
};

#endif // BCSPLINEALGORITHM_H
