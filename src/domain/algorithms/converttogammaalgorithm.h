#ifndef CONVERTTOGAMMAALGORITHM_H
#define CONVERTTOGAMMAALGORITHM_H

#include "../entities/image.h"

class ConvertToGammaAlgorithm
{
public:
    ConvertToGammaAlgorithm();

    void execute(Image *image, float from, float to);
};

#endif // CONVERTTOGAMMAALGORITHM_H
