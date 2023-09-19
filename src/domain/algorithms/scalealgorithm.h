#ifndef SCALEALGORITHM_H
#define SCALEALGORITHM_H

#include "algorithm.h"
#include "../entities/image.h"

class ScaleAlgorithm : public Algorithm
{
public:
    ScaleAlgorithm(Image image, double scale);

    virtual Image execute() override;

private:
    Image _image;
    double _scale;
};

#endif // SCALEALGORITHM_H
