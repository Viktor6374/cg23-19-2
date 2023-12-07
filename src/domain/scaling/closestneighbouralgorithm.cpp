#include "closestneighbouralgorithm.h"
#include <math.h>

ClosestNeighbourAlgorithm::ClosestNeighbourAlgorithm()
{
}

Image *ClosestNeighbourAlgorithm_scale_w(Image *image, int new_width, float shift)
{
    std::vector<Pixel> new_pixels(new_width * image->height());

    for (int j = 0; j < image->height(); ++j)
    {
        for (int i = 0; i < new_width; ++i)
        {
            float scaled_pixel_pos = (float)i / new_width * image->width() + shift;
            int rounded_pixel_pos = (int)round(scaled_pixel_pos);
            rounded_pixel_pos = fmaxf(0, rounded_pixel_pos);
            rounded_pixel_pos = fminf(image->width() - 1, rounded_pixel_pos);

            new_pixels[i + j * new_width] = image->pixels()[rounded_pixel_pos + j * image->width()];
        }
    }

    return new Image(new_width, image->height(), new_pixels);
}

Image *ClosestNeighbourAlgorithm_scale_h(Image *image, int new_height, float shift)
{
    std::vector<Pixel> new_pixels(image->width() * new_height);

    for (int i = 0; i < image->width(); ++i)
    {
        for (int j = 0; j < new_height; ++j)
        {
            float scaled_pixel_pos = (float)j / new_height * image->height() + shift;
            int rounded_pixel_pos = (int)round(scaled_pixel_pos);
            rounded_pixel_pos = fmaxf(0, rounded_pixel_pos);
            rounded_pixel_pos = fminf(image->height() - 1, rounded_pixel_pos);

            new_pixels[i + j * image->width()] = image->pixels()[i + rounded_pixel_pos * image->width()];
        }
    }

    return new Image(image->width(), new_height, new_pixels);
}

Image *ClosestNeighbourAlgorithm::execute(Image *image, int new_width, int new_height, Point shift)
{
    auto scaled_image1 = ClosestNeighbourAlgorithm_scale_w(image, new_width, shift.x);
    auto scaled_image2 = ClosestNeighbourAlgorithm_scale_h(scaled_image1, new_height, shift.y);

    delete scaled_image1;

    return scaled_image2;
}
