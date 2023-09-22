#include "p6imagesaver.h"

P6ImageSaver::P6ImageSaver()
{
}

void P6ImageSaver::save(Image *image, std::ofstream &out)
{
    out << "P6" << std::endl;
    out << image->width() << " " << image->height() << std::endl;
    out << 256 << std::endl;

    for (auto pixel : image->pixels())
    {
        out << pixel.red();
        out << pixel.green();
        out << pixel.blue();
    }
}
