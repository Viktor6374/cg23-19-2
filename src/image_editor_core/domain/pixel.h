#ifndef PIXEL_H
#define PIXEL_H


class Pixel
{
public:
    Pixel();

    Pixel(int red, int green, int blue);

    int get_red();
    int get_green();
    int get_blue();

private:
    int _red;
    int _green;
    int _blue;
};

#endif // PIXEL_H
