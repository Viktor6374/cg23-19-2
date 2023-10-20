#include "p6imagesaver.h"

P6ImageSaver::P6ImageSaver()
{
}

void P6ImageSaver::save(Image<BytePixel> *image, std::ofstream &out)
{
    out << "P6" << std::endl;
    out << image->width() << " " << image->height() << std::endl;
    out << 255 << std::endl;

    for (auto pixel : image->pixels())
    {
        for (int i = 0; i < 3; ++i)
        {
            out << (unsigned char)(pixel.channels[i] * 255);
        }
    }
}
