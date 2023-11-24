#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "../entities/image.h"
#include <vector>

class Histogram
{
public:
    Histogram(const std::vector<std::vector<int>> &channel_values);

    std::vector<std::vector<int>> &get_channel_values();

private:
    std::vector<std::vector<int>> _channel_values;
};

#endif // HISTOGRAM_H
