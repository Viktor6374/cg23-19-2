#ifndef ORDEREDDITHERINGALGORITHM_H
#define ORDEREDDITHERINGALGORITHM_H

#include "ditheringalgorithm.h"

class OrderedDitheringAlgorithm : public DitheringAlgorithm
{
public:
    OrderedDitheringAlgorithm();

    unsigned char *execute(Image *image, int bytes_count) override;
};

#endif // ORDEREDDITHERINGALGORITHM_H
