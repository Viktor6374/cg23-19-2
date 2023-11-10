#ifndef ATKINSONDITHERINGALGORITHM_H
#define ATKINSONDITHERINGALGORITHM_H

#include "ditheringalgorithm.h"

class AtkinsonDitheringAlgorithm : public DitheringAlgorithm
{
public:
    AtkinsonDitheringAlgorithm();

    unsigned char *execute(Image *image, int bytes_count) override;
};

#endif // ATKINSONDITHERINGALGORITHM_H
