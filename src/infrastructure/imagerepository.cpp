#include "imagerepository.h"

#include <fstream>

ImageRepository::ImageRepository(ImageLoaderFactory image_loader_factory, ImageSaverFactory image_saver_factory)
{
    _image_loader_factory = image_loader_factory;
    _image_saver_factory = image_saver_factory;
}

Image ImageRepository::load(std::string file_path)
{
    std::ifstream in(file_path);

    std::string image_type;
    in >> image_type;

    ImageLoader* loader = _image_loader_factory.create(image_type);

    Image image = loader->load(in);

    delete loader;

    return image;
}

void ImageRepository::save(const Image &image, std::string file_path, std::string image_type)
{
    std::ofstream out(file_path);

    ImageSaver* saver = _image_saver_factory.create(image_type);

    saver->save(image, out);

    delete saver;
}
