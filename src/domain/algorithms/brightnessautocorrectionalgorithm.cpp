#include "brightnessautocorrectionalgorithm.h"
#include "createhistogramalgorithm.h"
#include <cmath>

BrightnessAutocorrectionAlgorithm::BrightnessAutocorrectionAlgorithm()
{
}

float get_min(Histogram *hist, float skip)
{
    float res = 0;
    bool found = false;

    for (int i = 0; 2 * i < 256; ++i)
        for (int j = 0; j < 3; ++j)
            if (hist->get_channel_values()[j][i] != 0 && !found)
            {
                res =  i / 255.0;
                found = true;
            }

    res += skip;
    res = fmaxf(0, res);
    res = fminf(0.5, res);

    return res;
}

float get_max(Histogram *hist, float skip)
{
    float res = 1;
    bool found = false;

    for (int i = 255; 2 * i >= 256; --i)
        for (int j = 0; j < 3; ++j)
            if (hist->get_channel_values()[j][i] != 0 && !found)
            {
                res = i / 255.0;
                found = true;
            }

    res -= skip;
    res = fmaxf(0.5, res);
    res = fminf(1, res);

    return res;
}

void BrightnessAutocorrectionAlgorithm::execute(Image *image, float skip)
{
    auto create_hist_alg = CreateHistogramAlgorithm();
    Histogram *hist = create_hist_alg.execute(image, "Disabled", 8);

    float min = get_min(hist, skip);
    float max = get_max(hist, skip);

    for (auto &pixel : image->pixels())
    {
        for (auto &channel : pixel.channels)
        {
            channel = (channel - min) / (max - min);
            channel = fmaxf(channel, 0);
            channel = fminf(channel, 1);
        }
    }

    delete hist;
}
