#include "histogram.h"

Histogram::Histogram(const std::vector<std::vector<int>> &channel_values)
{
    _channel_values = channel_values;
}

std::vector<std::vector<int>> &Histogram::get_channel_values()
{
    return _channel_values;
}
