#ifndef SCALEALGORITHM_H
#define SCALEALGORITHM_H


#include "../entities/image.h"

class ScaleAlgorithm
{
public:
    ScaleAlgorithm();

    Image execute(const Image& image, double scale);
};

#endif // SCALEALGORITHM_H
