#include "imagesaver.h"

ImageSaver::ImageSaver()
{
    _dithering_algorithm_factory = new DitheringAlgorithmFactory();
}

ImageSaver::~ImageSaver()
{
    delete _dithering_algorithm_factory;
}
