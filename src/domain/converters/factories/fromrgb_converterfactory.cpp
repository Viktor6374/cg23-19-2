#include "fromrgb_converterfactory.h"
#include "../from_rgb/torgb_fromrgb_converter.h"
#include "../from_rgb/tohsl_fromrgb_converter.h"
#include "../from_rgb/tohsv_fromrgb_converter.h"
#include "../from_rgb/toycbcr601_fromrgb_converter.h"
#include "../from_rgb/toycbcr709_fromrgb_converter.h"
#include "../from_rgb/toycocg_fromrgb_converter.h"
#include "../from_rgb/tocmy_fromrgb_converter.h"
#include <stdexcept>

FromRGB_ConverterFactory::FromRGB_ConverterFactory()
{
}

FromRGB_Converter *FromRGB_ConverterFactory::create(ColorSpace to)
{
    switch (to)
    {
    case RGB : return new ToRGB_FromRGB_Converter();
    case HSL : return new ToHSL_FromRGB_Converter();
    case HSV : return new ToHSV_FromRGB_Converter();
    case YCbCr609 : return new ToYCbCr609_FromRGB_Converter();
    case YCbCr709 : return new ToYCbCr709_FromRGB_Converter();
    case YCoCg : return new ToYCoCg_FromRGB_Converter();
    case CMY : return new ToCMY_FromRGB_Converter();
    default : throw std::logic_error("Unsupported conversion");
    }
}
