#ifndef PNGIMAGESAVER_H
#define PNGIMAGESAVER_H

#include "imagesaver.h"

class pngimagesaver : public ImageSaver
{
public:
    pngimagesaver();

    virtual void save(Image *image, std::ofstream &out, std::string dithering_type, int bytes_count) override;
};

#endif // PNGIMAGESAVER_H
