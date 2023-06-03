cmake_minimum_required(VERSION 3.5)

set(namespace "QT_USER")
project("FlowLayoutLibrary" VERSION 0.1)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if (PROJECT_IS_TOP_LEVEL)
        message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
       message(STATUS "This project is a top-level one")
endif()

add_library(${PROJECT_NAME} SHARED)         # TODO: dll/SHARED 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/flowlayout.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # there library will look for headers/sources
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        # there projects outside library will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # there external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers include/flowlayout.h)

# where to find our CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Installing)
