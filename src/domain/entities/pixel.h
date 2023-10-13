#ifndef PIXEL_H
#define PIXEL_H

template<typename TChannel>
class Pixel
{
public:
    Pixel();
    Pixel(TChannel channel_1, TChannel channel_2, TChannel channel_3);

    TChannel channel_1;
    TChannel channel_2;
    TChannel channel_3;
};

#endif // PIXEL_H
