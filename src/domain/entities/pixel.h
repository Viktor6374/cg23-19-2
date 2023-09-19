#ifndef PIXEL_H
#define PIXEL_H


class Pixel
{
public:
    Pixel();
    Pixel(int red, int green, int blue);

    int red();
    int green();
    int blue();

private:
    int _red;
    int _green;
    int _blue;
};

#endif // PIXEL_H
