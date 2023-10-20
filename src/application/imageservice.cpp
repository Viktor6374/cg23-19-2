#include "imageservice.h"

ImageService::ImageService()
{
    _image_repository = new ImageRepository();
    _color_space_converter = new ColorSpaceConverter();

    _current_image = nullptr;

    _current_color_space = RGB;
}

ImageService::~ImageService()
{
    delete _current_image;

    delete _image_repository;
    delete _color_space_converter;
}

ColorSpace ImageService::current_color_cpace()
{
    return _current_color_space;
}

Image *ImageService::current_image()
{
    return _current_image;
}

void ImageService::load_image(std::string file_path)
{
    delete _current_image;

    _current_image = _image_repository->load(file_path);
}

void ImageService::save_image(std::string file_path, std::string image_type)
{
    if (_current_image == nullptr)
        return;

    _image_repository->save(_current_image, file_path, image_type);
}

void ImageService::change_color_space(ColorSpace color_space)
{
    if (_current_image != nullptr)
        _color_space_converter->convert(_current_image, _current_color_space, color_space);

    _current_color_space = color_space;
}
