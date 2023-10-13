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

    Image *base_image();

    void load_image(std::string file_path);
    void save_image(std::string file_path, std::string image_type);

    void convert_image_to_color_space(std::string color_space);

private:
    ImageRepository *_image_repository;
    ColorSpaceConverter *_color_space_converter;

    Image *_current_image;
    ColorSpace _current_color_space;
};

#endif // IMAGESERVICE_H
