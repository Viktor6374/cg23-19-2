#include "atkinsonditheringalgorithm.h"
#include <cmath>

AtkinsonDitheringAlgorithm::AtkinsonDitheringAlgorithm()
{
}

void update_errors_atkinson(float *errors, float error, int i, int w, int h)
{
    error = error / 8;

    if (i + 3 < 3 * w * h)
        errors[i + 3] += error;

    if (i + 6 < 3 * w * h)
        errors[i + 6] += error;

    if (i + 3 * w + 3 < 3 * w * h)
        errors[i + 3 * w + 3] += error;

    if (i + 3 * w < 3 * w * h)
        errors[i + 3 * w] += error;

    if (i + 3 * w - 3 < 3 * w * h)
        errors[i + 3 * w - 3] += error;

    if (i + 6 * w < 3 * w * h)
        errors[i + 6 * w] += error;
}

unsigned char *AtkinsonDitheringAlgorithm::execute(Image *image, int bytes_count)
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
            update_errors_atkinson(errors, error, 3 * i + j, image->width(), image->height());
        }
    }

    return data;
}
