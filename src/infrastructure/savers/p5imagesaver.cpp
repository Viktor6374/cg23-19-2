#include "p5imagesaver.h"
#include <limits>

P5ImageSaver::P5ImageSaver()
{
}

void P5ImageSaver::save(Image *image, std::ofstream &out)
{
    out << "P5" << std::endl << image->width() << " " << image->height() << std::endl << 256 << std::endl;
    for (int i = 0; i < image->pixels().size(); i++){
        out << image->pixels()[i].red();
    }
}
