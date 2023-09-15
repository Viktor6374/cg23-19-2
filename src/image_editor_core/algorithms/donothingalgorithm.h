#ifndef DONOTHINGALGORITHM_H
#define DONOTHINGALGORITHM_H

#include "algorithm.h"

class DoNothingAlgorithm : public Algorithm
{
public:
    DoNothingAlgorithm(Image image);

    Image Execute() override;

private:
    Image _image;
};

#endif // DONOTHINGALGORITHM_H
