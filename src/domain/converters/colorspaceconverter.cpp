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
    ToRGB_Converter *to_rgb_converter = _to_rgb_converter_factory->create(from);
    FromRGB_Converter *from_rgb_converter = _from_rgb_converter_factory->create(to);

    to_rgb_converter->convert(image);
    from_rgb_converter->convert(image);

    delete to_rgb_converter;
    delete from_rgb_converter;
}
