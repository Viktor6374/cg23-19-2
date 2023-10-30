#include "imageservice.h"
#include "../domain/algorithms/converttogammaalgorithm.h"
#include "../domain/algorithms/drawlinealgorithm.h"

ImageService::ImageService()
{
    _image_repository = new ImageRepository();
    _color_space_converter = new ColorSpaceConverter();

    _current_image = nullptr;

    _current_color_space = RGB;
    _current_gamma = 2.2;
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

float ImageService::current_gamma()
{
    return _current_gamma;
}

Image *ImageService::current_image()
{
    return _current_image;
}

void ImageService::load_image(std::string file_path)
{
    delete _current_image;

    _current_image = _image_repository->load(file_path);
    _current_gamma = 2.2;

    auto alg = DrawLineAlgorithm();
    alg.execute(_current_image, Point(0, 0), Point(333, 333), 1, 1);
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

void ImageService::convert_to_gamma(float gamma)
{
    if (_current_image == nullptr)
        return;

    _color_space_converter->convert(_current_image, _current_color_space, RGB);

    auto algorithm = ConvertToGammaAlgorithm();

    algorithm.execute(_current_image, _current_gamma, gamma);

    _current_gamma = gamma;

    _color_space_converter->convert(_current_image, RGB, _current_color_space);
}

void ImageService::assing_gamma(float gamma)
{
    _current_gamma = gamma;
}
