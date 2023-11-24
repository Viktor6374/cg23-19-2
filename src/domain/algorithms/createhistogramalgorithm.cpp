#include "createhistogramalgorithm.h"

CreateHistogramAlgorithm::CreateHistogramAlgorithm()
{
    _dithering_algorithm_factory = new DitheringAlgorithmFactory();
}

CreateHistogramAlgorithm::~CreateHistogramAlgorithm()
{
    delete _dithering_algorithm_factory;
}

Histogram *CreateHistogramAlgorithm::execute(Image *image, std::string dithering_type, int bytes_count)
{
    auto dithering_algorithm = _dithering_algorithm_factory->create(dithering_type);

    unsigned char *data = dithering_algorithm->execute(image, bytes_count);

    std::vector<std::vector<int>> channel_values(3, std::vector<int>(256, 0));

    for (int i = 0; i < 3 * image->pixels().size(); ++i)
    {
        ++channel_values[i % 3][data[i]];
    }

    return new Histogram(channel_values);
}
