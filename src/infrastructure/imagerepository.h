#ifndef IMAGEREPOSITORY_H
#define IMAGEREPOSITORY_H


#include "../domain/entities/image.h"
#include "factories/imageloaderfactory.h"
#include "factories/imagesaverfactory.h"
#include <string>

class ImageRepository
{
public:
    ImageRepository(ImageLoaderFactory image_loader_factory, ImageSaverFactory image_saver_factory);

    Image load(std::string file_path);

    void save(const Image& image, std::string file_path, std::string image_type);

private:
    ImageLoaderFactory _image_loader_factory;
    ImageSaverFactory _image_saver_factory;
};

#endif // IMAGEREPOSITORY_H