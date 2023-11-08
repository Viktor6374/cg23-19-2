#ifndef DITHERINGALGORITHM_H
#define DITHERINGALGORITHM_H

#include "../entities/image.h"

class DitheringAlgorithm
{
public:
    DitheringAlgorithm();
    virtual ~DitheringAlgorithm();

    virtual unsigned char *execute(Image *image, int bytes_count) = 0;
};

#endif // DITHERINGALGORITHM_H
