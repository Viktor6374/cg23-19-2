#ifndef IMAGESERVICE_H
#define IMAGESERVICE_H

#include "../domain/entities/image.h"
#include "../infrastructure/imagerepository.h"
#include "../domain/converters/colorspaceconverter.h"
#include "../domain/models/colorspace.h"
#include "../domain/models/point.h"
#include "../domain/scaling/scalingalgorithm.h"
#include "../domain/filters/imagefilter.h"
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
    void save_image(std::string file_path, std::string image_type, std::string dithering_type, int bytes_count);

    void generate_gradient(int w, int h);

    void change_color_space(ColorSpace color_space);

    void draw_line(Point point1, Point point2, Pixel color, float didth, float trans);

    void convert_to_gamma(float gamma);
    void assing_gamma(float gamma);

    void autocorrect_brightness(float skip);

    void scale(int new_width, int new_height, Point shift, ScalingAlgorithm *algorithm);

    void use_filter(ImageFilter *filter);

private:
    ImageRepository *_image_repository;
    ColorSpaceConverter *_color_space_converter;

    Image *_current_image;
    ColorSpace _current_color_space;
    float _current_gamma;
};

#endif // IMAGESERVICE_H
