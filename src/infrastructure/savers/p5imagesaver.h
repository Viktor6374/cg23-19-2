#ifndef P5IMAGESAVER_H
#define P5IMAGESAVER_H

#include "imagesaver.h"

class P5ImageSaver : public ImageSaver
{
public:
    P5ImageSaver();

    virtual void save(Image *image, const std::ofstream &out) override;
};

#endif // P5IMAGESAVER_H
