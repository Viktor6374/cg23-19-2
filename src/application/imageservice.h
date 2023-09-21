#ifndef IMAGESERVICE_H
#define IMAGESERVICE_H

#include "../domain/entities/image.h"
#include "../infrastructure/imagerepository.h"
#include <string>

class ImageService
{
public:
    ImageService();
    ~ImageService();

    Image *base_image();

    void load_image(std::string file_path);
    void save_image(std::string file_path, std::string image_type);

private:
    ImageRepository *_image_repository;

    Image *_base_image;
};

#endif // IMAGESERVICE_H
