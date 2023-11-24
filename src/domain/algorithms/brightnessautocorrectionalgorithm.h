#ifndef BRIGHTNESSAUTOCORRECTIONALGORITHM_H
#define BRIGHTNESSAUTOCORRECTIONALGORITHM_H

#include "../entities/image.h"

class BrightnessAutocorrectionAlgorithm
{
public:
    BrightnessAutocorrectionAlgorithm();

    void execute(Image *image, float skip);
};

#endif // BRIGHTNESSAUTOCORRECTIONALGORITHM_H
