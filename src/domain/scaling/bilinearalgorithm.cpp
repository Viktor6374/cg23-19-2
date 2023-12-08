#include "bilinearalgorithm.h"
#include <cmath>

BilinearAlgorithm::BilinearAlgorithm()
{
}

Image *BilinearAlgorithm_scale_w(Image *image, int new_width, float shift)
{
    std::vector<Pixel> new_pixels(new_width * image->height());

    for (int j = 0; j < image->height(); ++j)
    {
        for (int i = 0; i < new_width; ++i)
        {
            float scaled_pixel_pos = (float)i / new_width * image->width() + shift;
            scaled_pixel_pos = fmaxf(0, scaled_pixel_pos);
            scaled_pixel_pos = fminf(image->width() - 1, scaled_pixel_pos);
            int prev_pixel_pos = (int)scaled_pixel_pos;
            int next_pixel_pos = prev_pixel_pos + 1;

            if (scaled_pixel_pos == roundf(scaled_pixel_pos))
            {
                int rounded_pixel_pos = (int)round(scaled_pixel_pos);
                rounded_pixel_pos = fmaxf(0, rounded_pixel_pos);
                rounded_pixel_pos = fminf(image->width() - 1, rounded_pixel_pos);

                new_pixels[i + j * new_width] = image->pixels()[rounded_pixel_pos + j * image->width()];
            }
            else
            {
                float k1 = 1 - (scaled_pixel_pos - prev_pixel_pos);
                float k2 = 1 - (next_pixel_pos - scaled_pixel_pos);

                Pixel prev_pixel = image->pixels()[prev_pixel_pos + j * image->width()];
                Pixel next_pixel = image->pixels()[next_pixel_pos + j * image->width()];

                Pixel new_pixel = Pixel(
                            prev_pixel.channels[0] * k1 + next_pixel.channels[0] * k2,
                            prev_pixel.channels[1] * k1 + next_pixel.channels[1] * k2,
                            prev_pixel.channels[2] * k1 + next_pixel.channels[2] * k2);

                new_pixels[i + j * new_width] = new_pixel;
            }
        }
    }

    return new Image(new_width, image->height(), new_pixels);
}

Image *BilinearAlgorithm_scale_h(Image *image, int new_height, float shift)
{
    std::vector<Pixel> new_pixels(image->width() * new_height);

    for (int i = 0; i < image->width(); ++i)
    {
        for (int j = 0; j < new_height; ++j)
        {
            float scaled_pixel_pos = (float)j / new_height * image->height() + shift;
            scaled_pixel_pos = fmaxf(0, scaled_pixel_pos);
            scaled_pixel_pos = fminf(image->height() - 1, scaled_pixel_pos);
            int prev_pixel_pos = (int)scaled_pixel_pos;
            int next_pixel_pos = prev_pixel_pos + 1;

            if (scaled_pixel_pos == roundf(scaled_pixel_pos))
            {
                int rounded_pixel_pos = (int)round(scaled_pixel_pos);
                rounded_pixel_pos = fmaxf(0, rounded_pixel_pos);
                rounded_pixel_pos = fminf(image->height() - 1, rounded_pixel_pos);

                new_pixels[i + j * image->width()] = image->pixels()[i + rounded_pixel_pos * image->width()];
            }
            else
            {
                float k1 = 1 - (scaled_pixel_pos - prev_pixel_pos);
                float k2 = 1 - (next_pixel_pos - scaled_pixel_pos);

                Pixel prev_pixel = image->pixels()[i + prev_pixel_pos * image->width()];
                Pixel next_pixel = image->pixels()[i + next_pixel_pos * image->width()];

                Pixel new_pixel = Pixel(
                            prev_pixel.channels[0] * k1 + next_pixel.channels[0] * k2,
                            prev_pixel.channels[1] * k1 + next_pixel.channels[1] * k2,
                            prev_pixel.channels[2] * k1 + next_pixel.channels[2] * k2);

                new_pixels[i + j * image->width()] = new_pixel;
            }
        }
    }

    return new Image(image->width(), new_height, new_pixels);
}

Image *BilinearAlgorithm::execute(Image *image, int new_width, int new_height, Point shift)
{
    auto scaled_image1 = BilinearAlgorithm_scale_w(image, new_width, shift.x);
    auto scaled_image2 = BilinearAlgorithm_scale_h(scaled_image1, new_height, shift.y);

    delete scaled_image1;

    return scaled_image2;
}
