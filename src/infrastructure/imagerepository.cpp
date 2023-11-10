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

Image<BytePixel> *ImageRepository::load(std::string file_path)
{
    std::ifstream in(file_path, std::ios::binary);

    std::string image_type;
    in >> image_type;

    ImageLoader* loader = _image_loader_factory->create(image_type);

    Image<BytePixel> *image = loader->load(in);

    delete loader;

    return image;
}

void ImageRepository::save(Image *image, std::string file_path, std::string image_type, std::string dithering_type, int bytes_count)
{
    std::ofstream out(file_path, std::ios::binary);

    ImageSaver* saver = _image_saver_factory->create(image_type);

    saver->save(image, out, dithering_type, bytes_count);

    delete saver;
}
