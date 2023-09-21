#include "imagerepository.h"

#include <fstream>

ImageRepository::ImageRepository()
{
    _image_loader_factory = new ImageLoaderFactory();
    _image_saver_factory = new ImageSaverFactory();
}

ImageRepository::~ImageRepository()
{
    delete _image_loader_factory;
    delete _image_saver_factory;
}

Image *ImageRepository::load(std::string file_path)
{
    std::ifstream in(file_path, std::ios::binary);

    std::string image_type;
    in >> image_type;

    ImageLoader* loader = _image_loader_factory->create(image_type);

    Image *image = loader->load(in);

    delete loader;

    return image;
}

void ImageRepository::save(Image *image, std::string file_path, std::string image_type)
{
    std::ofstream out(file_path);

    ImageSaver* saver = _image_saver_factory->create(image_type);

    saver->save(image, out);

    delete saver;
}
