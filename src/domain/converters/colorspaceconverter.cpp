#include "colorspaceconverter.h"

ColorSpaceConverter::ColorSpaceConverter()
{
    _to_rgb_converter_factory = new ToRGB_ConverterFactory();
    _from_rgb_converter_factory = new FromRGB_ConverterFactory();
}

ColorSpaceConverter::~ColorSpaceConverter()
{
    delete  _to_rgb_converter_factory;
    delete  _from_rgb_converter_factory;
}


void ColorSpaceConverter::convert(Image *image, ColorSpace from, ColorSpace to)
{
    ToRGB_Converter *to_tgb_converter = _to_rgb_converter_factory->create(from);
    FromRGB_Converter *from_tgb_converter = _from_rgb_converter_factory->create(to);

    to_tgb_converter->convert(image);
    from_tgb_converter->convert(image);

    delete to_tgb_converter;
    delete from_tgb_converter;
}
