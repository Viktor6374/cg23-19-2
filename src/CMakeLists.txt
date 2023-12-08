cmake_minimum_required(VERSION 3.5)

project(ImageEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        domain/entities/pixel.h domain/entities/pixel.cpp
        domain/entities/image.h domain/entities/image.cpp

        domain/models/colorspace.h
        domain/models/point.h domain/models/point.cpp
        domain/models/histogram.h domain/models/histogram.cpp

        domain/converters/colorspaceconverter.h domain/converters/colorspaceconverter.cpp

        domain/algorithms/converttogammaalgorithm.h domain/algorithms/converttogammaalgorithm.cpp
        domain/algorithms/drawlinealgorithm.h domain/algorithms/drawlinealgorithm.cpp
        domain/algorithms/createhistogramalgorithm.h domain/algorithms/createhistogramalgorithm.cpp
        domain/algorithms/drawhistogramalgorithm.h domain/algorithms/drawhistogramalgorithm.cpp
        domain/algorithms/brightnessautocorrectionalgorithm.h domain/algorithms/brightnessautocorrectionalgorithm.cpp
        domain/algorithms/channel1autocorrectionalgorithm.h domain/algorithms/channel1autocorrectionalgorithm.cpp

        domain/converters/to_rgb/torgb_converter.h domain/converters/to_rgb/torgb_converter.cpp
        domain/converters/to_rgb/fromrgb_torgb_converter.h domain/converters/to_rgb/fromrgb_torgb_converter.cpp
        domain/converters/to_rgb/fromhsl_torgb_converter.h domain/converters/to_rgb/fromhsl_torgb_converter.cpp
        domain/converters/to_rgb/fromhsv_torgb_converter.h domain/converters/to_rgb/fromhsv_torgb_converter.cpp
        domain/converters/to_rgb/fromycbcr601_torgb_converter.h domain/converters/to_rgb/fromycbcr601_torgb_converter.cpp
        domain/converters/to_rgb/fromycbcr709_torgb_converter.h domain/converters/to_rgb/fromycbcr709_torgb_converter.cpp
        domain/converters/to_rgb/fromycocg_torgb_converter.h domain/converters/to_rgb/fromycocg_torgb_converter.cpp
        domain/converters/to_rgb/fromcmy_torgb_converter.h domain/converters/to_rgb/fromcmy_torgb_converter.cpp

        domain/converters/from_rgb/fromrgb_converter.h domain/converters/from_rgb/fromrgb_converter.cpp
        domain/converters/from_rgb/torgb_fromrgb_converter.h domain/converters/from_rgb/torgb_fromrgb_converter.cpp
        domain/converters/from_rgb/tohsl_fromrgb_converter.h domain/converters/from_rgb/tohsl_fromrgb_converter.cpp
        domain/converters/from_rgb/tohsv_fromrgb_converter.h domain/converters/from_rgb/tohsv_fromrgb_converter.cpp
        domain/converters/from_rgb/toycbcr601_fromrgb_converter.h domain/converters/from_rgb/toycbcr601_fromrgb_converter.cpp
        domain/converters/from_rgb/toycbcr709_fromrgb_converter.h domain/converters/from_rgb/toycbcr709_fromrgb_converter.cpp
        domain/converters/from_rgb/toycocg_fromrgb_converter.h domain/converters/from_rgb/toycocg_fromrgb_converter.cpp
        domain/converters/from_rgb/tocmy_fromrgb_converter.h domain/converters/from_rgb/tocmy_fromrgb_converter.cpp

        domain/converters/factories/torgb_converterfactory.h domain/converters/factories/torgb_converterfactory.cpp
        domain/converters/factories/fromrgb_converterfactory.h domain/converters/factories/fromrgb_converterfactory.cpp

        domain/dithering/ditheringalgorithm.h domain/dithering/ditheringalgorithm.cpp
        domain/dithering/noditheringalgorithm.h domain/dithering/noditheringalgorithm.cpp
        domain/dithering/orderedditheringalgorithm.h domain/dithering/orderedditheringalgorithm.cpp
        domain/dithering/randomditheringalgorithm.h domain/dithering/randomditheringalgorithm.cpp
        domain/dithering/floydstainbergditheringalgorithm.h domain/dithering/floydstainbergditheringalgorithm.cpp
        domain/dithering/atkinsonditheringalgorithm.h domain/dithering/atkinsonditheringalgorithm.cpp

        domain/factories/ditheringalgorithmfactory.h domain/factories/ditheringalgorithmfactory.cpp

        domain/scaling/scalingalgorithm.h domain/scaling/scalingalgorithm.cpp
        domain/scaling/closestneighbouralgorithm.h domain/scaling/closestneighbouralgorithm.cpp
        domain/scaling/bilinearalgorithm.h domain/scaling/bilinearalgorithm.cpp
        domain/scaling/lanczos3algorithm.h domain/scaling/lanczos3algorithm.cpp
        domain/scaling/bcsplinealgorithm.h domain/scaling/bcsplinealgorithm.cpp

        application/imageservice.h application/imageservice.cpp

        infrastructure/imagerepository.h infrastructure/imagerepository.cpp

        infrastructure/loaders/imageloader.h infrastructure/loaders/imageloader.cpp
        infrastructure/loaders/p5imageloader.h infrastructure/loaders/p5imageloader.cpp
        infrastructure/loaders/p6imageloader.h infrastructure/loaders/p6imageloader.cpp

        infrastructure/savers/imagesaver.h infrastructure/savers/imagesaver.cpp
        infrastructure/savers/p5imagesaver.h infrastructure/savers/p5imagesaver.cpp
        infrastructure/savers/p6imagesaver.h infrastructure/savers/p6imagesaver.cpp

        infrastructure/factories/imageloaderfactory.h infrastructure/factories/imageloaderfactory.cpp
        infrastructure/factories/imagesaverfactory.h infrastructure/factories/imagesaverfactory.cpp

        presentation/models/linedrawingoptions.h presentation/models/linedrawingoptions.cpp
        presentation/models/ditheringoptions.h presentation/models/ditheringoptions.cpp

        presentation/converters/imageconverter.h presentation/converters/imageconverter.cpp

        presentation/imageeditor.h presentation/imageeditor.cpp presentation/imageeditor.ui

        presentation/widgets/nearestneighbourinputwidget.h presentation/widgets/nearestneighbourinputwidget.cpp
        presentation/widgets/bilinearinputwidget.h presentation/widgets/bilinearinputwidget.cpp
        presentation/widgets/lanczos3inputwidget.h presentation/widgets/lanczos3inputwidget.cpp
        presentation/widgets/bcsplineinputwidget.h presentation/widgets/bcsplineinputwidget.cpp

        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ImageEditor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ImageEditor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ImageEditor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ImageEditor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ImageEditor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(ImageEditor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ImageEditor)
endif()
