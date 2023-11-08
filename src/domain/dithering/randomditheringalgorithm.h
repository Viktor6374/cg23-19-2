#ifndef RANDOMDITHERINGALGORITHM_H
#define RANDOMDITHERINGALGORITHM_H

#include "ditheringalgorithm.h"

class RandomDitheringAlgorithm : public DitheringAlgorithm
{
public:
    RandomDitheringAlgorithm();

    unsigned char *execute(Image *image, int bytes_count) override;
};

#endif // RANDOMDITHERINGALGORITHM_H
