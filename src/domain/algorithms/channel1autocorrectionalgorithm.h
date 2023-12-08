#ifndef CHANNEL1AUTOCORRECTIONALGORITHM_H
#define CHANNEL1AUTOCORRECTIONALGORITHM_H

#include "../entities/image.h"

class Channel1AutocorrectionAlgorithm
{
public:
    Channel1AutocorrectionAlgorithm();

    void execute(Image *image, float skip);
};

#endif // CHANNEL1AUTOCORRECTIONALGORITHM_H
