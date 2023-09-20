#include "imageservice.h"

ImageService::ImageService()
{
    _image_repository = new ImageRepository();
}

ImageService::~ImageService()
{
    delete _image_repository;
}
