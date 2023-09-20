#ifndef IMAGESERVICE_H
#define IMAGESERVICE_H

#include "../infrastructure/imagerepository.h"

class ImageService
{
public:
    ImageService();
    ~ImageService();

private:
    ImageRepository *_image_repository;
};

#endif // IMAGESERVICE_H
