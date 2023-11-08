#include "ditheringalgorithmfactory.h"
#include "../dithering/noditheringalgorithm.h"
#include "../dithering/orderedditheringalgorithm.h"
#include "../dithering/randomditheringalgorithm.h"
#include "../dithering/floydstainbergditheringalgorithm.h"
#include "../dithering/atkinsonditheringalgorithm.h"
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
    else if (type == "Ordered")
    {
        return new OrderedDitheringAlgorithm();
    }
    else if (type == "Random")
    {
        return new RandomDitheringAlgorithm();
    }
    else if (type == "Floyd-Stainberg")
    {
        return new FloydStainbergDitheringAlgorithm();
    }
    else if (type == "Atkinson")
    {
        return new AtkinsonDitheringAlgorithm();
    }
    else
    {
        throw std::logic_error("unsupported dithering type");
    }
}
