cmake_minimum_required(VERSION 3.21)
project(LabyrinthGenerator)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/maze/*.cpp)
file(GLOB HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/maze/*.h)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core)
qt_standard_project_setup()

add_executable(LabyrinthGenerator ${SOURCES} ${HEADERS})

target_link_libraries(LabyrinthGenerator PRIVATE 
    Qt6::Core
    Qt6::Widgets
)
