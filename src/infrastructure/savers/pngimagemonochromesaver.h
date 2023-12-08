#ifndef PNGIMAGEMONOCHROMESAVER_H
#define PNGIMAGEMONOCHROMESAVER_H

#include "imagesaver.h"

class pngimagemonochromesaver : public ImageSaver
{
public:
    pngimagemonochromesaver();

    virtual void save(Image *image, std::ofstream &out, std::string dithering_type, int bytes_count) override;
};

#endif // PNGIMAGEMONOCHROMESAVER_H
