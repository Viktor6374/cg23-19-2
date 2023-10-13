#include "torgb_converterfactory.h"
#include "../to_rgb/fromrgb_torgb_converter.h"
#include "../to_rgb/fromhsl_torgb_converter.h"
#include "../to_rgb/fromhsv_torgb_converter.h"
#include "../to_rgb/fromycbcr609_torgb_converter.h"
#include "../to_rgb/fromycbcr709_torgb_converter.h"
#include "../to_rgb/fromycocg_torgb_converter.h"
#include "../to_rgb/fromcmy_torgb_converter.h"
#include <stdexcept>

ToRGB_ConverterFactory::ToRGB_ConverterFactory()
{
}

ToRGB_Converter *ToRGB_ConverterFactory::create(ColorSpace from)
{
    switch (from)
    {
    case RGB : return new FromRGB_ToRGB_Converter();
    case HSL : return new FromHSL_ToRGB_Converter();
    case HSV : return new FromHSV_ToRGB_Converter();
    case YCbCr609 : return new FromYCbCr609_ToRGB_Converter();
    case YCbCr709 : return new FromYCbCr709_ToRGB_Converter();
    case YCoCg : return new FromYCoCg_ToRGB_Converter();
    case CMY : return new FromCMY_ToRGB_Converter();
    default : throw std::logic_error("Unsupported conversion");
    }
}
