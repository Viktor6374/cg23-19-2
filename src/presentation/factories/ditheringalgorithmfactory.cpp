#include "ditheringalgorithmfactory.h"
#include "../dithering/noditheringalgorithm.h"
#include <stdexcept>

DitheringAlgorithmFactory::DitheringAlgorithmFactory()
{
}

DitheringAlgorithm *DitheringAlgorithmFactory::create(std::string type)
{
    if (type == "Disabled")
    {
        return new NoDitheringAlgorithm();
    }
    else
    {
        throw std::logic_error("unsupported dithering type");
    }
}
