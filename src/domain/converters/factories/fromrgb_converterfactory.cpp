#include "fromrgb_converterfactory.h"
#include "../from_rgb/torgb_fromrgb_converter.h"
#include <stdexcept>

FromRGB_ConverterFactory::FromRGB_ConverterFactory()
{
}

FromRGB_Converter *FromRGB_ConverterFactory::create(ColorSpace to)
{
    if (to == RGB)
    {
        return new ToRGB_FromRGB_Converter();
    }
    else
    {
        throw std::logic_error("Unsupported conversion");
    }
}
