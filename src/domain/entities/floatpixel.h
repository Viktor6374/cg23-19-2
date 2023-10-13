#ifndef FLOATPIXEL_H
#define FLOATPIXEL_H

#include "pixel.h"

class FloatPixel : public Pixel<float>
{
public:
    FloatPixel();
    FloatPixel(float channel_1, float channel_2, float channel_3);
};

#endif // FLOATPIXEL_H
