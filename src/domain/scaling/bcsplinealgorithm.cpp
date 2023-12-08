#include "bcsplinealgorithm.h"
#include <cmath>

BCSplineAlgorithm::BCSplineAlgorithm(float b, float c)
{
    _b = b;
    _c = c;
}

float bc_spline_kernel(float x, float b, float c)
{
    if (x < 0)
        x = -x;

    if (x < 1)
        return ((12 - 9 * b - 6 * c) * fabsf(x * x * x) + (-18 + 12 * b + 6 * c) * x * x + 6 - 2 * b) / 6;

    if (x < 2)
        return ((-b - 6 * c) * fabsf(x * x * x) + (6 * b + 30 * c) * x * x + (-12 * b - 48 * c) * fabsf(x) + 8 * b + 24 * c) / 6;

    return 0;
}

Image *BCSplineAlgorithm_scale_w(Image *image, int new_width, float shift, float b, float c)
{
    std::vector<Pixel> new_pixels(new_width * image->height());

    for (int j = 0; j < image->height(); ++j)
    {
        for (int i = 0; i < new_width; ++i)
        {
            float scaled_pixel_pos = (float)i / new_width * image->width() + shift;

                        Pixel mixed_pixel = Pixel(0, 0, 0);

                        for (int k = -5; k <= 5; ++k)
                        {
                            int rounded_pixel_pos = scaled_pixel_pos + k;
                            float kernel = bc_spline_kernel(rounded_pixel_pos - scaled_pixel_pos, b, c);

                            if (rounded_pixel_pos < 0)
                            {
                                mixed_pixel.channels[0] += image->pixel_at(0, j).channels[0] * kernel;
                                mixed_pixel.channels[1] += image->pixel_at(0, j).channels[1] * kernel;
                                mixed_pixel.channels[2] += image->pixel_at(0, j).channels[2] * kernel;
                            }
                            else if (rounded_pixel_pos >= image->width())
                            {
                                mixed_pixel.channels[0] += image->pixel_at(image->width() - 1, j).channels[0] * kernel;
                                mixed_pixel.channels[1] += image->pixel_at(image->width() - 1, j).channels[1] * kernel;
                                mixed_pixel.channels[2] += image->pixel_at(image->width() - 1, j).channels[2] * kernel;
                            }
                            else
                            {
                                mixed_pixel.channels[0] += image->pixel_at(rounded_pixel_pos, j).channels[0] * kernel;
                                mixed_pixel.channels[1] += image->pixel_at(rounded_pixel_pos, j).channels[1] * kernel;
                                mixed_pixel.channels[2] += image->pixel_at(rounded_pixel_pos, j).channels[2] * kernel;
                            }
                        }

                        for (int k = 0; k < 3; ++k)
                        {
                            mixed_pixel.channels[k] = fmaxf(0, mixed_pixel.channels[k]);
                            mixed_pixel.channels[k] = fminf(1, mixed_pixel.channels[k]);
                        }

                        new_pixels[i + j * new_width] = mixed_pixel;
        }
    }

    return new Image(new_width, image->height(), new_pixels);
}

Image *BCSplineAlgorithm_scale_h(Image *image, int new_height, float shift, float b, float c)
{
    std::vector<Pixel> new_pixels(image->width() * new_height);

    for (int i = 0; i < image->width(); ++i)
    {
        for (int j = 0; j < new_height; ++j)
        {
            float scaled_pixel_pos = (float)j / new_height * image->height() + shift;

            Pixel mixed_pixel = Pixel(0, 0, 0);

            for (int k = -5; k <= 5; ++k)
            {
                int rounded_pixel_pos = scaled_pixel_pos + k;
                float kernel = bc_spline_kernel(rounded_pixel_pos - scaled_pixel_pos, b, c);

                if (rounded_pixel_pos < 0)
                {
                    mixed_pixel.channels[0] += image->pixel_at(i, 0).channels[0] * kernel;
                    mixed_pixel.channels[1] += image->pixel_at(i, 0).channels[1] * kernel;
                    mixed_pixel.channels[2] += image->pixel_at(i, 0).channels[2] * kernel;
                }
                else if (rounded_pixel_pos >= image->height())
                {
                    mixed_pixel.channels[0] += image->pixel_at(i, image->height() - 1).channels[0] * kernel;
                    mixed_pixel.channels[1] += image->pixel_at(i, image->height() - 1).channels[1] * kernel;
                    mixed_pixel.channels[2] += image->pixel_at(i, image->height() - 1).channels[2] * kernel;
                }
                else
                {
                    mixed_pixel.channels[0] += image->pixel_at(i, rounded_pixel_pos).channels[0] * kernel;
                    mixed_pixel.channels[1] += image->pixel_at(i, rounded_pixel_pos).channels[1] * kernel;
                    mixed_pixel.channels[2] += image->pixel_at(i, rounded_pixel_pos).channels[2] * kernel;
                }
            }

            for (int k = 0; k < 3; ++k)
            {
                mixed_pixel.channels[k] = fmaxf(0, mixed_pixel.channels[k]);
                mixed_pixel.channels[k] = fminf(1, mixed_pixel.channels[k]);
            }

            new_pixels[i + j * image->width()] = mixed_pixel;
        }
    }

    return new Image(image->width(), new_height, new_pixels);
}

Image *BCSplineAlgorithm::execute(Image *image, int new_width, int new_height, Point shift)
{
    auto scaled_image1 = BCSplineAlgorithm_scale_w(image, new_width, shift.x, _b, _c);
    auto scaled_image2 = BCSplineAlgorithm_scale_h(scaled_image1, new_height, shift.y, _b, _c);

    delete scaled_image1;

    return scaled_image2;
}
