#include "floydstainbergditheringalgorithm.h"
#include <cmath>

FloydStainbergDitheringAlgorithm::FloydStainbergDitheringAlgorithm()
{
}

void update_errors_floyd_stainberg(float *errors, float error, int i, int w, int h)
{
    error = error / 16;

    if (i + 3 < 3 * w * h)
        errors[i + 3] += 7 * error;

    if (i + 3 * w + 3 < 3 * w * h)
        errors[i + 3 * w + 3] += error;

    if (i + 3 * w < 3 * w * h)
        errors[i + 3 * w] += 5 * error;

    if (i + 3 * w - 3 < 3 * w * h)
        errors[i + 3 * w - 3] += 3 * error;
}

unsigned char *FloydStainbergDitheringAlgorithm::execute(Image *image, int bytes_count)
{
    int byte_size = 1 << bytes_count;

    unsigned char *data = new unsigned char[image->pixels().size() * 3];
    float *errors = new float[image->pixels().size() * 3];

    for (int i = 0; i < 3 * image->pixels().size(); ++i)
        errors[i] = 0;

    for (int i = 0; i < image->pixels().size(); ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            float value = image->pixels()[i].channels[j] + errors[3 * i + j];
            value = fminf(1, value);
            value = fmaxf(0, value);

            int channel = (unsigned char)round(value * (byte_size - 1));
            channel *= 255;
            channel /= byte_size - 1;

            data[3 * i + j] = channel;

            float error = value - channel / 255.0;
            update_errors_floyd_stainberg(errors, error, 3 * i + j, image->width(), image->height());
        }
    }

    return data;
}
