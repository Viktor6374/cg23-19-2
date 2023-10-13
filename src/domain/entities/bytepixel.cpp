#include "bytepixel.h"

BytePixel::BytePixel()
    : Pixel(0, 0, 0)
{
}

BytePixel::BytePixel(unsigned char channel_1, unsigned char channel_2, unsigned char channel_3)
    : Pixel(channel_1, channel_2, channel_3)
{
}
