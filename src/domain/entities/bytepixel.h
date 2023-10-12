#ifndef BYTEPIXEL_H
#define BYTEPIXEL_H

#include "pixel.h"

class BytePixel : public Pixel<unsigned char>
{
public:
    BytePixel();
    BytePixel(unsigned char channel_1, unsigned char channel_2, unsigned char channel_3);
};

#endif // BYTEPIXEL_H
