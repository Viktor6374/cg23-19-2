#ifndef CREATEHISTOGRAMALGORITHM_H
#define CREATEHISTOGRAMALGORITHM_H

#include "../models/histogram.h"
#include "../factories/ditheringalgorithmfactory.h"
#include <string>

class CreateHistogramAlgorithm
{
public:
    CreateHistogramAlgorithm();
    ~CreateHistogramAlgorithm();

    Histogram *execute(Image *image, std::string dithering_type, int bytes_count);

private:
    DitheringAlgorithmFactory *_dithering_algorithm_factory;
};

#endif // CREATEHISTOGRAMALGORITHM_H
