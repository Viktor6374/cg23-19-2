#include "channel1autocorrectionalgorithm.h"
#include "createhistogramalgorithm.h"
#include <cmath>

Channel1AutocorrectionAlgorithm::Channel1AutocorrectionAlgorithm()
{
}

float get_min1(Histogram *hist, float skip)
{
    float res = 0;
    bool found = false;

    for (int i = 0; 2 * i < 256; ++i)
        if (hist->get_channel_values()[0][i] != 0 && !found)
        {
            res =  i / 255.0;
            found = true;
        }

    res += skip;
    res = fmaxf(0, res);
    res = fminf(0.5, res);

    return res;
}

float get_max1(Histogram *hist, float skip)
{
    float res = 1;
    bool found = false;

    for (int i = 255; 2 * i >= 256; --i)
        if (hist->get_channel_values()[0][i] != 0 && !found)
        {
            res = i / 255.0;
            found = true;
        }

    res -= skip;
    res = fmaxf(0.5, res);
    res = fminf(1, res);

    return res;
}

void Channel1AutocorrectionAlgorithm::execute(Image *image, float skip)
{
    auto create_hist_alg = CreateHistogramAlgorithm();
    Histogram *hist = create_hist_alg.execute(image, "Disabled", 8);

    float min = get_min1(hist, skip);
    float max = get_max1(hist, skip);

    for (auto &pixel : image->pixels())
    {
        pixel.channels[0] = (pixel.channels[0] - min) / (max - min);
        pixel.channels[0] = fmaxf(pixel.channels[0], 0);
        pixel.channels[0] = fminf(pixel.channels[0], 1);
    }

    delete hist;
}
