#include "orderedditheringalgorithm.h"
#include <cmath>

OrderedDitheringAlgorithm::OrderedDitheringAlgorithm()
{
}

const int M[8][8] = { { 0, 32, 8, 40, 2, 34, 10, 42 },
                      { 48, 16, 56, 24, 50, 18, 58, 26 },
                      { 12, 44, 4, 36, 14, 46, 6, 38 },
                      { 60, 28, 52, 20, 62, 30, 54, 22 },
                      { 3, 35, 11, 43, 1, 33, 9, 41 },
                      { 51, 19, 59, 27, 49, 17, 57, 25 },
                      { 15, 47, 7, 39, 13, 45, 5, 37 },
                      { 63, 31, 55, 23, 61, 29, 53, 21 } };

float get_m(int i, int w)
{
    int x = i % w;
    int y = i / w;
    x %= 8;
    y %= 8;

    return M[x][y] / 64.0;
}

unsigned char *OrderedDitheringAlgorithm::execute(Image *image, int bytes_count)
{
    int byte_size = 1 << bytes_count;

    unsigned char *data = new unsigned char[image->pixels().size() * 3];

    for (int i = 0; i < image->pixels().size(); ++i)
    {
        float m = get_m(i, image->width());

        for (int j = 0; j < 3; ++j)
        {
            float value = image->pixels()[i].channels[j];
            value += (m - 0.5) / bytes_count;
            value = fminf(1, value);
            value = fmaxf(0, value);

            int channel = (unsigned char)round(value * (byte_size - 1));
            channel *= 255;
            channel /= byte_size - 1;

            data[3 * i + j] = channel;
        }
    }

    return data;
}
