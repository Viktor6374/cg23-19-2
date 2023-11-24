#ifndef DRAWHISTOGRAMALGORITHM_H
#define DRAWHISTOGRAMALGORITHM_H

#include "../entities/image.h"

class DrawHistogramAlgorithm
{
public:
    DrawHistogramAlgorithm();

    Image *execute(const std::vector<int> &channel_values);
};

#endif // DRAWHISTOGRAMALGORITHM_H
