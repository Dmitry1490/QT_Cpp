cmake_minimum_required(VERSION 3.16)

project(Two_rows_detection LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Tesseract REQUIRED IMPORTED_TARGET tesseract lept)
add_library(Tesseract::libtesseract ALIAS PkgConfig::Tesseract)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(Two_rows_detection
  main.cpp
)
target_link_libraries(Two_rows_detection Qt${QT_VERSION_MAJOR}::Core)

target_link_libraries(Two_rows_detection libopencv_core.dll.a)
target_link_libraries(Two_rows_detection libopencv_highgui.dll.a)
target_link_libraries(Two_rows_detection libopencv_imgcodecs.dll.a)
target_link_libraries(Two_rows_detection libopencv_imgproc.dll.a)

target_link_libraries(Two_rows_detection Tesseract::libtesseract)

include(GNUInstallDirs)
install(TARGETS Two_rows_detection
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
