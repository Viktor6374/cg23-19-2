#include "pixel.h"

template<typename TChannel>
Pixel<TChannel>::Pixel()
{
    channel_1 = TChannel();
    channel_2 = TChannel();
    channel_3 = TChannel();
}

template<typename TChannel>
Pixel<TChannel>::Pixel(TChannel channel_1, TChannel channel_2, TChannel channel_3)
{
    this->channel_1 = channel_1;
    this->channel_2 = channel_1;
    this->channel_3 = channel_1;
}
