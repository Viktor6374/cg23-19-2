#ifndef NODITHERINGALGORITHM_H
#define NODITHERINGALGORITHM_H

#include "ditheringalgorithm.h"

class NoDitheringAlgorithm : public DitheringAlgorithm
{
public:
    NoDitheringAlgorithm();

    unsigned char *execute(Image *image, int bytes_count) override;
};

#endif // NODITHERINGALGORITHM_H
