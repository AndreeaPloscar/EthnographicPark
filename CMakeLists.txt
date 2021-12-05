cmake_minimum_required(VERSION 3.19)
project(e2_915_Ploscar_Andreea_c)

set(CMAKE_CXX_STANDARD 14)

include_directories(../../CLionProjects/e2-915-Ploscar-Andreea-c)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_PREFIX_PATH "/Users/andreeaploscar/Qt/5.15.2/clang_64/lib/cmake")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
add_executable(e2_915_Ploscar_Andreea_c main.cpp
        Building.cpp
        Building.h
        Ethnologist.cpp
        Ethnologist.h
        Repository.cpp
        Repository.h
        Service.cpp
        Service.h
        Gui.cpp
        Gui.h)
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Charts)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Charts)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
