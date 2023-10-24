#ifndef IMAGESERVICE_H
#define IMAGESERVICE_H

#include "../domain/entities/image.h"
#include "../infrastructure/imagerepository.h"
#include "../domain/converters/colorspaceconverter.h"
#include "../domain/models/colorspace.h"
#include <string>

class ImageService
{
public:
    ImageService();
    ~ImageService();

    ColorSpace current_color_cpace();
    float current_gamma();
    Image *current_image();

    void load_image(std::string file_path);
    void save_image(std::string file_path, std::string image_type);

    void change_color_space(ColorSpace color_space);

    void convert_to_gamma(float gamma);
    void assing_gamma(float gamma);

private:
    ImageRepository *_image_repository;
    ColorSpaceConverter *_color_space_converter;

    Image *_current_image;
    ColorSpace _current_color_space;
    float _current_gamma;
};

#endif // IMAGESERVICE_H
