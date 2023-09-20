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

    const Image& base_image();

    void load_image(std::string file_path);

private:
    ImageRepository *_image_repository;

    Image _base_image;
};

#endif // IMAGESERVICE_H
