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
#include "../src/domain/converters/to_rgb/fromycbcr601_torgb_converter.cpp"
#include "../src/domain/converters/to_rgb/fromycbcr709_torgb_converter.cpp"
#include "../src/domain/converters/to_rgb/fromycocg_torgb_converter.cpp"
#include "../src/domain/converters/to_rgb/fromcmy_torgb_converter.cpp"

#include "../src/domain/converters/from_rgb/fromrgb_converter.cpp"
#include "../src/domain/converters/from_rgb/torgb_fromrgb_converter.cpp"
#include "../src/domain/converters/from_rgb/tohsl_fromrgb_converter.cpp"
#include "../src/domain/converters/from_rgb/tohsv_fromrgb_converter.cpp"
#include "../src/domain/converters/from_rgb/toycbcr601_fromrgb_converter.cpp"
#include "../src/domain/converters/from_rgb/toycbcr709_fromrgb_converter.cpp"
#include "../src/domain/converters/from_rgb/toycocg_fromrgb_converter.cpp"
#include "../src/domain/converters/from_rgb/tocmy_fromrgb_converter.cpp"

#include "../src/domain/algorithms/converttogammaalgorithm.h"
#include "../src/domain/algorithms/converttogammaalgorithm.cpp"



class ImageEditorTests : public QObject
{
    Q_OBJECT

public:
    ImageEditorTests();
    ~ImageEditorTests();

private slots:
    void convert_XXXtoYYYtoXXX_test();
    void convert_gamma_test();
};

ImageEditorTests::ImageEditorTests()
{
}

ImageEditorTests::~ImageEditorTests()
{
}

void ImageEditorTests::convert_XXXtoYYYtoXXX_test()
{
    auto converter = ColorSpaceConverter();

    for (int XXX = RGB; XXX <= CMY; ++XXX)
    {
        for  (int YYY = RGB; YYY <= CMY; ++YYY)
        {
            Pixel pixel = Pixel(0.5, 0.5, 0.5);
            Image image = Image(1, 1, std::vector<Pixel>(1, pixel));

            converter.convert(&image, (ColorSpace)XXX, (ColorSpace)YYY);
            converter.convert(&image, (ColorSpace)YYY, (ColorSpace)XXX);

//            QCOMPARE(image.pixels()[0].channels[0], pixel.channels[0]);
//            QCOMPARE(image.pixels()[0].channels[1], pixel.channels[1]);
//            QCOMPARE(image.pixels()[0].channels[2], pixel.channels[2]);
        }
    }
}

void ImageEditorTests::convert_gamma_test()
{
    auto algorithm = ConvertToGammaAlgorithm();

    Pixel pixel = Pixel(0.5, 0.5, 0.5);
    Image image = Image(1, 1, std::vector<Pixel>(1, pixel));

    algorithm.execute(&image, 2.2, 1);
    algorithm.execute(&image, 1, 2.2);

    QCOMPARE(image.pixels()[0].channels[0], pixel.channels[0]);
    QCOMPARE(image.pixels()[0].channels[1], pixel.channels[1]);
    QCOMPARE(image.pixels()[0].channels[2], pixel.channels[2]);
}

QTEST_APPLESS_MAIN(ImageEditorTests)

#include "tst_imageeditortests.moc"
