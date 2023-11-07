#include "noditheringalgorithm.h"

NoDitheringAlgorithm::NoDitheringAlgorithm()
{
}

unsigned char *NoDitheringAlgorithm::execute(Image *image, int bytes_count)
{
    int byte_size = 1 << bytes_count;

    unsigned char *data = new unsigned char[image->pixels().size() * 3];

    for (int i = 0; i < image->pixels().size(); ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            int channel = (unsigned char)(image->pixels()[i].channels[j] * byte_size);

            data[3 * i + j] = (unsigned char)(channel * 256 / byte_size);
        }
    }

    return data;
}
