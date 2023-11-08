#include "randomditheringalgorithm.h"
#include <random>
#include <cmath>

RandomDitheringAlgorithm::RandomDitheringAlgorithm()
{
}

float random_float(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

float random_round(float x)
{
    float border = random_float(0.001, 9.999);
    float x_mod = fmodf(x, 1);

    if (x_mod >= border)
        return x - x_mod + 1;
    else
        return x - x_mod;
}

unsigned char *RandomDitheringAlgorithm::execute(Image *image, int bytes_count)
{
    int byte_size = 1 << bytes_count;

    unsigned char *data = new unsigned char[image->pixels().size() * 3];

    for (int i = 0; i < image->pixels().size(); ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            int channel = (unsigned char)random_round(image->pixels()[i].channels[j] * (byte_size - 1));
            channel *= 255;
            channel /= byte_size - 1;

            data[3 * i + j] = channel;
        }
    }

    return data;
}
