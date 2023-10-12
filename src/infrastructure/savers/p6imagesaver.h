#ifndef P6IMAGESAVER_H
#define P6IMAGESAVER_H

#include "imagesaver.h"

class P6ImageSaver : public ImageSaver
{
public:
    P6ImageSaver();

    virtual void save(Image<BytePixel> *image, std::ofstream &out) override;
};

#endif // P6IMAGESAVER_H
