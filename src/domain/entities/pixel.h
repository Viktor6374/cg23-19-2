#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
public:
    Pixel();
    Pixel(unsigned char red, unsigned char green, unsigned char blue);

    unsigned char red() const;
    unsigned char green() const;
    unsigned char blue() const;

private:
    unsigned char _red;
    unsigned char _green;
    unsigned char _blue;
};

#endif // PIXEL_H
