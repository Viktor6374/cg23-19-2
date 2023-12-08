#include "imageservice.h"
#include "../domain/algorithms/converttogammaalgorithm.h"
#include "../domain/algorithms/drawlinealgorithm.h"
#include "../domain/algorithms/brightnessautocorrectionalgorithm.h"
#include "../domain/algorithms/channel1autocorrectionalgorithm.h"

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
}

void ImageService::save_image(std::string file_path, std::string image_type, std::string dithering_type, int bytes_count)
{
    if (_current_image == nullptr)
        return;

    _image_repository->save(_current_image, file_path, image_type, dithering_type, bytes_count);
}

void ImageService::generate_gradient(int w, int h)
{
    std::vector<Pixel> pixels(w * h);

    for (int i = 0; i < w; ++i)
    {
        float color = (float)i / w;

        for (int j = 0; j < h; ++j)
        {
            pixels[i + j * w].channels[0] = color;
            pixels[i + j * w].channels[1] = color;
            pixels[i + j * w].channels[2] = color;
        }
    }

    Image *gradient = new Image(w, h, pixels);

    delete _current_image;

    _current_image = gradient;
    _current_gamma = 2.2;
    _current_color_space = RGB;
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

void ImageService::draw_line(Point point1, Point point2, Pixel color, float width, float trans)
{
    _color_space_converter->convert(_current_image, _current_color_space, RGB);

    auto alg = DrawLineAlgorithm();
    alg.execute(_current_image, point1, point2, color, width, trans);

    _color_space_converter->convert(_current_image, RGB, _current_color_space);

}

void ImageService::autocorrect_brightness(float skip)
{
    if (_current_color_space == YCbCr601
            || _current_color_space == YCbCr709
            || _current_color_space == YCoCg)
    {
        auto algorithm = Channel1AutocorrectionAlgorithm();
        algorithm.execute(_current_image, skip);
    }
    else
    {
        _color_space_converter->convert(_current_image, _current_color_space, RGB);

        auto algorithm = BrightnessAutocorrectionAlgorithm();
        algorithm.execute(_current_image, skip);

        _color_space_converter->convert(_current_image, RGB, _current_color_space);
    }
}

void ImageService::scale(int new_width, int new_height, Point shift, ScalingAlgorithm *algorithm)
{
    if (_current_image == nullptr)
            return;

    auto scaler = ConvertToGammaAlgorithm();
    scaler.execute(_current_image, _current_gamma, 1);

    Image *scaled_image = algorithm->execute(_current_image, new_width, new_height, shift);

    delete _current_image;

    _current_image = scaled_image;

    scaler.execute(_current_image, 1, _current_gamma);
}
