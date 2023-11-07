#ifndef DITHERINGALGORITHMFACTORY_H
#define DITHERINGALGORITHMFACTORY_H

#include "../dithering/ditheringalgorithm.h"
#include <string>

class DitheringAlgorithmFactory
{
public:
    DitheringAlgorithmFactory();

    DitheringAlgorithm *create(std::string type);
};

#endif // DITHERINGALGORITHMFACTORY_H
