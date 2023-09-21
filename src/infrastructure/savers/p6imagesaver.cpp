#include "p6imagesaver.h"

P6ImageSaver::P6ImageSaver()
{
}

void P6ImageSaver::save(Image *image, std::ofstream &out)
{
    out << "P6" << std::endl << image->width() << " " << image->height() << std::endl << 256 << std::endl;
    for (int i = 0; i < image->pixels().size(); i++){
        out.write(image->pixels[i].red(), 1);
        out.write(image->pixels[i].green(), 1);
        out.write(image->pixels[i].blue(), 1);
    }
}
