#include "torgb_converterfactory.h"
#include "../to_rgb/fromrgb_torgb_converter.h"
#include <stdexcept>

ToRGB_ConverterFactory::ToRGB_ConverterFactory()
{
}

ToRGB_Converter *ToRGB_ConverterFactory::create(ColorSpace to)
{
    if (to == RGB)
    {
        return new FromRGB_ToRGB_Converter();
    }
    else
    {
        throw std::logic_error("Unsupported conversion");
    }
}
