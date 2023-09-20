#include "imageservice.h"

ImageService::ImageService()
{
    _image_repository = new ImageRepository();

    _base_image = Image();
}

ImageService::~ImageService()
{
    delete _image_repository;
}

const Image& ImageService::base_image()
{
    return _base_image;
}

void ImageService::load_image(std::string file_path)
{
    _base_image = _image_repository->load(file_path);
}
