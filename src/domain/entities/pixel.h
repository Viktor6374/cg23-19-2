#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
public:
    Pixel();
    Pixel(float channel_1, float channel_2, float channel_3);
    Pixel(const Pixel& pixel);

    float channels[3];
};

#endif // PIXEL_H
