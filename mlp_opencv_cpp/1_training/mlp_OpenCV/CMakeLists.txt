cmake_minimum_required(VERSION 3.16)

project(mlp_OpenCV LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(mlp_OpenCV
  main.cpp
)
target_link_libraries(mlp_OpenCV Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(mlp_OpenCV libopencv_core.dll.a)
target_link_libraries(mlp_OpenCV libopencv_highgui.dll.a)
target_link_libraries(mlp_OpenCV libopencv_imgcodecs.dll.a)
target_link_libraries(mlp_OpenCV libopencv_ml.dll.a)

include(GNUInstallDirs)
install(TARGETS mlp_OpenCV
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
