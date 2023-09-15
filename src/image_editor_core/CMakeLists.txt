cmake_minimum_required(VERSION 3.5)

project(image_editor_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(image_editor_core
    domain/pixel.h domain/pixel.cpp
    algorithms/algorithm.h algorithms/algorithm.cpp
    domain/image.h domain/image.cpp
    algorithms/donothingalgorithm.h algorithms/donothingalgorithm.cpp)

include(GNUInstallDirs)
install(TARGETS image_editor_core
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
