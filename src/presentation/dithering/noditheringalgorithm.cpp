#include "noditheringalgorithm.h"

NoDitheringAlgorithm::NoDitheringAlgorithm()
{
}

unsigned char *NoDitheringAlgorithm::execute(Image *image, int bytes_count)
{
    unsigned char *data = new unsigned char[image->pixels().size() * 3];

    for (int i = 0; i < image->pixels().size(); ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            data[3 * i + j] = (unsigned char)(image->pixels()[i].channels[j] * 255);
        }
    }

    return data;
}
