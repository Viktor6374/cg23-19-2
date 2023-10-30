#ifndef LINEDRAWINGOPTIONS_H
#define LINEDRAWINGOPTIONS_H

#include "../../domain/entities/pixel.h"
#include "../../domain/models/point.h"

class LineDrawingOptions
{
public:
    LineDrawingOptions();

    Point *point1;

    Pixel color;

    float width;
    float trans;
};

#endif // LINEDRAWINGOPTIONS_H
