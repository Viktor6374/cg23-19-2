#include "p5imagesaver.h"
#include <limits>

P5ImageSaver::P5ImageSaver()
{
}

void P5ImageSaver::save(Image *image, std::ofstream &out)
{
    out << "P5" << std::endl;
    out << image->width() << " " << image->height() << std::endl;
    out << 255 << std::endl;

    for (auto pixel : image->pixels())
    {
        out << (char)pixel.channels[0];
    }
}
