#include <QtTest>

#include "../src/domain/converters/colorspaceconverter.h"

#include "../src/domain/entities/pixel.cpp"
#include "../src/domain/entities/image.cpp"

#include "../src/domain/converters/colorspaceconverter.cpp"

#include "../src/domain/converters/factories/fromrgb_converterfactory.cpp"
#include "../src/domain/converters/factories/torgb_converterfactory.cpp"

#include "../src/domain/converters/to_rgb/torgb_converter.cpp"
#include "../src/domain/converters/to_rgb/fromrgb_torgb_converter.cpp"
#include "../src/domain/converters/to_rgb/fromhsl_torgb_converter.cpp"
#include "../src/domain/converters/to_rgb/fromhsv_torgb_converter.cpp"
#include "../src/domain/converters/to_rgb/fromycbcr609_torgb_converter.cpp"
#include "../src/domain/converters/to_rgb/fromycbcr709_torgb_converter.cpp"
#include "../src/domain/converters/to_rgb/fromycocg_torgb_converter.cpp"
#include "../src/domain/converters/to_rgb/fromcmy_torgb_converter.cpp"

#include "../src/domain/converters/from_rgb/fromrgb_converter.cpp"
#include "../src/domain/converters/from_rgb/torgb_fromrgb_converter.cpp"
#include "../src/domain/converters/from_rgb/tohsl_fromrgb_converter.cpp"
#include "../src/domain/converters/from_rgb/tohsv_fromrgb_converter.cpp"
#include "../src/domain/converters/from_rgb/toycbcr609_fromrgb_converter.cpp"
#include "../src/domain/converters/from_rgb/toycbcr709_fromrgb_converter.cpp"
#include "../src/domain/converters/from_rgb/toycocg_fromrgb_converter.cpp"
#include "../src/domain/converters/from_rgb/tocmy_fromrgb_converter.cpp"


class ImageEditorTests : public QObject
{
    Q_OBJECT

public:
    ImageEditorTests();
    ~ImageEditorTests();

private slots:
    void convert_test();

};

ImageEditorTests::ImageEditorTests()
{
}

ImageEditorTests::~ImageEditorTests()
{
}

void ImageEditorTests::convert_test()
{
    Pixel pixel = Pixel(0, 0, 0);
    Image image = Image(1, 1, std::vector<Pixel>(1, pixel));

    auto converter = ColorSpaceConverter();

    converter.convert(&image, HSL, RGB);

    assert(image.pixels()[0].channels[0] == 0);
    assert(image.pixels()[0].channels[1] == 0);
    assert(image.pixels()[0].channels[2] == 0);
}

QTEST_APPLESS_MAIN(ImageEditorTests)

#include "tst_imageeditortests.moc"
