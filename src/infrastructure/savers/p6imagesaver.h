#ifndef P6IMAGESAVER_H
#define P6IMAGESAVER_H

#include "imagesaver.h"

class P6ImageSaver : public ImageSaver
{
public:
    P6ImageSaver();

    virtual void save(Image *image, std::ofstream &out, std::string dithering_type, int bytes_count) override;
};

#endif // P6IMAGESAVER_H
