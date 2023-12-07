#include "pngimagesaver.h"

pngimagesaver::pngimagesaver()
{

}

void pngimagesaver::save(Image *image, std::ofstream &out, std::string dithering_type, int bytes_count){
    unsigned char signature[8] {137, 80, 78, 71, 13, 10, 26, 10};
    out << signature;

    auto algorithm = _dithering_algorithm_factory->create(dithering_type);
    unsigned char *data = algorithm->execute(image, bytes_count);

    out << (int)13;
    out << "IHDR";
    out << (int)image->width() << (int)image->height() << (unsigned char)8 << (unsigned char)2 << (unsigned char)0 << (unsigned char)0 << (unsigned char)0;
}

