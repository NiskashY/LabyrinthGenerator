cmake_minimum_required(VERSION 3.5)

project(LabyrinthGenerator VERSION 0.1 LANGUAGES CXX)

# SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Include directories | compiler will search there
set(COMMON_INCLUDE ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDE})

# Define cpp files
file(GLOB SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/maze/*.cpp
    ${PROJECT_SOURCE_DIR}/src/ui/*.cpp
)

# Define .h files for QtCreator
file(GLOB HDR_FILES
    ${COMMON_INCLUDE}/*.h
)

# Define .ui files for QtCreator
file(GLOB UI_FILES
    ${PROJECT_SOURCE_DIR}/src/*.ui
    ${PROJECT_SOURCE_DIR}/src/maze/*.ui
    ${PROJECT_SOURCE_DIR}/src/ui/*.ui
)

# Define all the files to be linked 
set(PROJECT_SOURCES
    ${SRC_FILES}
    ${HDR_FILES}
    ${UI_FILES}

    images/resourses.qrc
    images/stylesheet.qss
)

# Qt connection stuff 
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LabyrinthGenerator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET LabyrinthGenerator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(LabyrinthGenerator)
endif()
