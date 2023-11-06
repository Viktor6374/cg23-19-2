#ifndef DRAWLINEALGORITHM_H
#define DRAWLINEALGORITHM_H

#include "../entities/image.h"
#include "../models/point.h"

class DrawLineAlgorithm
{
public:
    DrawLineAlgorithm();

    void execute(Image *image, Point point1, Point point2, Pixel color, float width, float trans);
};

#endif // DRAWLINEALGORITHM_H
