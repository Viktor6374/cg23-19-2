#include "donothingalgorithm.h"

DoNothingAlgorithm::DoNothingAlgorithm(Image image)
{
    _image = image;
}

Image DoNothingAlgorithm::Execute()
{
    return _image;
}
