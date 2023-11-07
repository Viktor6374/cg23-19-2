#ifndef DITHERINGALGORITHM_H
#define DITHERINGALGORITHM_H

#include "../../domain/entities/image.h"

class DitheringAlgorithm
{
public:
    DitheringAlgorithm();

    virtual unsigned char *execute(Image *image) = 0;
};

#endif // DITHERINGALGORITHM_H
