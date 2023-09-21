#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "../entities/image.h"

class Algorithm
{
public:
    Algorithm();

    virtual Image execute() = 0;
};

#endif // ALGORITHM_H
