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
        domain/algorithms/scalealgorithm.h domain/algorithms/scalealgorithm.cpp

        infrastructure/imagerepository.h infrastructure/imagerepository.cpp

        infrastructure/loaders/imageloader.h infrastructure/loaders/imageloader.cpp
        infrastructure/loaders/p5imageloader.h infrastructure/loaders/p5imageloader.cpp
        infrastructure/loaders/p6imageloader.h infrastructure/loaders/p6imageloader.cpp

        infrastructure/savers/imagesaver.h infrastructure/savers/imagesaver.cpp
        infrastructure/savers/p5imagesaver.h infrastructure/savers/p5imagesaver.cpp
        infrastructure/savers/p6imagesaver.h infrastructure/savers/p6imagesaver.cpp

        infrastructure/factories/imageloaderfactory.h infrastructure/factories/imageloaderfactory.cpp
        infrastructure/factories/imagesaverfactory.h infrastructure/factories/imagesaverfactory.cpp

        presentation/imageconverter.h presentation/imageconverter.cpp

        mainwindow.cpp mainwindow.h mainwindow.ui

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
