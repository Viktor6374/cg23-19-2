#include "p6imagesaver.h"

P6ImageSaver::P6ImageSaver()
{
}

void P6ImageSaver::save(Image *image, std::ofstream &out, std::string dithering_type, int bytes_count)
{
    out << "P6" << std::endl;
    out << image->width() << " " << image->height() << std::endl;
    out << 255 << std::endl;

    auto algorithm = _dithering_algorithm_factory->create(dithering_type);
    unsigned char *data = algorithm->execute(image, bytes_count);

    for (int i = 0; i < image->pixels().size() * 3; ++i)
    {
        out << data[i];
    }

    delete algorithm;
    delete [] data;
}
