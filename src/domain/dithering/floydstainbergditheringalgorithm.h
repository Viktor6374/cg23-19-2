#ifndef FLOYDSTAINBERGDITHERINGALGORITHM_H
#define FLOYDSTAINBERGDITHERINGALGORITHM_H

#include "ditheringalgorithm.h"

class FloydStainbergDitheringAlgorithm : public DitheringAlgorithm
{
public:
    FloydStainbergDitheringAlgorithm();

    unsigned char *execute(Image *image, int bytes_count) override;
};

#endif // FLOYDSTAINBERGDITHERINGALGORITHM_H
