#include "scalealgorithm.h"
#include <cmath>

ScaleAlgorithm::ScaleAlgorithm(Image image, double scale)
{
    _image = image;
    _scale = scale;
}

Image ScaleAlgorithm::execute()
{
    double k = sqrt(_scale);

    return Image();
}
