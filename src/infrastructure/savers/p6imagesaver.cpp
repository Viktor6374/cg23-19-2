#include "p6imagesaver.h"

P6ImageSaver::P6ImageSaver()
{
}

void P6ImageSaver::save(Image *image, std::ofstream &out)
{
    out << "P6" << std::endl << image->width() << " " << image->height() << std::endl << 256 << std::endl;
    for (int i = 0; i < image->pixels().size(); i++){
        out << image->pixels()[i].red();
        out << image->pixels()[i].green();
        out << image->pixels()[i].blue();
    }
}
