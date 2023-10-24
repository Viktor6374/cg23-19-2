#include "converttogammaalgorithm.h"
#include <cmath>

ConvertToGammaAlgorithm::ConvertToGammaAlgorithm()
{
}

void convert_channel_to_gamma(float &channel, float from, float to)
{
     channel = powf(channel, from);
     channel = powf(channel, 1 / to);
}

void ConvertToGammaAlgorithm::execute(Image *image, float from, float to)
{
    for (auto &pixel : image->pixels())
        for (auto &channel : pixel.channels)
            convert_channel_to_gamma(channel, from, to);
}
