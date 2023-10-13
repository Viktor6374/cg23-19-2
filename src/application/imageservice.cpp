#include "imageservice.h"
#include "../domain/entities/bytepixel.h"
#include "../domain/entities/floatpixel.h"

ImageService::ImageService()
{
    _image_repository = new ImageRepository();

    _base_image = nullptr;
}

ImageService::~ImageService()
{
    delete _base_image;

    delete _image_repository;
}

Image<FloatPixel> *ImageService::base_image()
{
    return _base_image;
}

void ImageService::load_image(std::string file_path)
{
    delete _base_image;

    _base_image = _image_repository->load(file_path);
}

void ImageService::save_image(std::string file_path, std::string image_type)
{
    _image_repository->save(_base_image, file_path, image_type);
}
