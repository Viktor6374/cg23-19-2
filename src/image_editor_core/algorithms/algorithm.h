#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "../domain/image.h"

class Algorithm
{
public:
    Algorithm();

    virtual Image Execute() = 0;
};

#endif // ALGORITHM_H
