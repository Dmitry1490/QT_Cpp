cmake_minimum_required(VERSION 3.16)

project(testing_mnist_opencv LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(testing_mnist_opencv
  main.cpp
)
target_link_libraries(testing_mnist_opencv Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(testing_mnist_opencv libopencv_core.dll.a)
target_link_libraries(testing_mnist_opencv libopencv_highgui.dll.a)
target_link_libraries(testing_mnist_opencv libopencv_imgcodecs.dll.a)
target_link_libraries(testing_mnist_opencv libopencv_ml.dll.a)
target_link_libraries(testing_mnist_opencv libopencv_imgproc.dll.a)


include(GNUInstallDirs)
install(TARGETS testing_mnist_opencv
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
