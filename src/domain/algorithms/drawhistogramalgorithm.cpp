#include "drawhistogramalgorithm.h"
#include <algorithm>

DrawHistogramAlgorithm::DrawHistogramAlgorithm()
{
}

Image *DrawHistogramAlgorithm::execute(const std::vector<int> &channel_values)
{
    std::vector<Pixel> pixels(256 * 100, Pixel(1, 1, 1));

    int max_value = *std::max_element(channel_values.begin(), channel_values.end());

    for (int i = 0; i < 256; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            float normalized_value = 100.0 * channel_values[i] / max_value;

            if (j <= normalized_value)
                pixels[256 * (99 - j) + i] = Pixel(0, 0, 0);
        }
    }

    return new Image(256, 100, pixels);
}
