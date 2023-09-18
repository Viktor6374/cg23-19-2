#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <string>
#include "../core/domain/image.h"

class ImageLoader
{
public:
    ImageLoader();

    Image load(std::string file_path);

    void save(Image image, std::string file_path);
};

#endif // IMAGELOADER_H
