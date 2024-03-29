#include "drawlinealgorithm.h"
#include <vector>
#include <cmath>

DrawLineAlgorithm::DrawLineAlgorithm()
{
}


Point plot(int x, int y, float c) {
    return Point(x, y, c);
}

int ipart(float x) {
    return std::floor(x);
}

int fround(float x) {
    return ipart(x + 0.5);
}

float fpart(float x) {
    return x - ipart(x);
}

float rfpart(float x) {
    return 1 - fpart(x);
}

std::vector<Point> drawLine(int x0, int y0, int x1, int y1, int width) {
    int offset_1 = width / 2;
    int offset_2 = width / 2 + width % 2;

    std::vector<Point> result;
    bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);

    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    float dx = x1 - x0;
    float dy = y1 - y0;

    float gradient;
    if (dx == 0.0f) {
        gradient = 1.0f;
    } else {
        gradient = dy / dx;
    }

    // handle first endpoint
    int xend = round(x0);
    float yend = y0 + gradient * (xend - x0);
    float xgap = rfpart(x0 + 0.5f);
    int xpxl1 = xend; // this will be used in the main loop
    int ypxl1 = ipart(yend);
    if (steep) {
        result.push_back(plot(ypxl1,   xpxl1, rfpart(yend) * xgap));
        result.push_back(plot(ypxl1+1, xpxl1, fpart(yend) * xgap));
    } else {
        result.push_back(plot(xpxl1, ypxl1,   rfpart(yend) * xgap));
        result.push_back(plot(xpxl1, ypxl1+1, fpart(yend) * xgap));
    }
    float intery = yend + gradient; // first y-intersection for the main loop

    // handle second endpoint
    xend = fround(x1);
    yend = y1 + gradient * (xend - x1);
    xgap = fpart(x1 + 0.5f);
    int xpxl2 = xend; // this will be used in the main loop
    int ypxl2 = ipart(yend);
    if (steep) {
        result.push_back(plot(ypxl2 - offset_1,   xpxl2, rfpart(yend) * xgap));
        for (int i = ypxl2 - offset_1 + 1; i < ypxl2+1 + offset_2; i++){
            result.push_back(plot(i, xpxl2, 1.0));
        }
        result.push_back(plot(ypxl2+1 + offset_2, xpxl2, fpart(yend) * xgap));
    } else {
        result.push_back(plot(xpxl2, ypxl2 - offset_1,   rfpart(yend) * xgap));
        for (int i = ypxl2 - offset_1 + 1; i < ypxl2+1 + offset_2; i++){
            result.push_back(plot(xpxl2, i, 1.0));
        }
        result.push_back(plot(xpxl2, ypxl2+1 + offset_2, fpart(yend) * xgap));
    }

    // main loop
    if (steep) {
        for (int x = xpxl1 + 1; x < xpxl2; x++) {
            result.push_back(plot(ipart(intery) - offset_1,   x, rfpart(intery)));
            for (int i = ipart(intery) - offset_1 + 1; i < ipart(intery)+1 + offset_2; i++){
                result.push_back(plot(i, x, 1.0));
            }
            result.push_back(plot(ipart(intery)+1 + offset_2, x, fpart(intery)));
            intery += gradient;
        }
    } else {
        for (int x = xpxl1 + 1; x < xpxl2; x++) {
            result.push_back(plot(x, ipart(intery) - offset_1,   rfpart(intery)));
            for (int i = ipart(intery) - offset_1 + 1; i < ipart(intery)+1 + offset_2; i++){
                result.push_back(plot(x, i, 1.0));
            }
            result.push_back(plot(x, ipart(intery)+1 + offset_2, fpart(intery)));
            intery += gradient;
        }
    }

    return result;
}

void DrawLineAlgorithm::execute(Image *image, Point point1, Point point2, Pixel color, float width, float trans)
{
    for (const auto &point : drawLine(point1.x, point1.y, point2.x, point2.y, width)){
        Pixel current_pixel = image->pixels()[image->width()*point.y + point.x];
        Pixel new_color = Pixel(color.channels[0] * point.trans * trans + current_pixel.channels[0] * (1 - point.trans * trans),
                                color.channels[1] * point.trans * trans + current_pixel.channels[1] * (1 - point.trans * trans),
                                color.channels[2] * point.trans * trans + current_pixel.channels[2] * (1 - point.trans * trans));
        image->pixels()[image->width()*point.y + point.x] = new_color;
    }
}
