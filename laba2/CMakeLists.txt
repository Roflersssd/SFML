cmake_minimum_required(VERSION 3.22)

project(laba2)

set(CMAKE_CXX_STANDARD 17)
file(GLOB CPP_SOURCES "src/main.cpp" "src/CubeClass/Cube.cpp")

include_directories("src/CubeClass/Cube.h")

add_executable(${PROJECT_NAME} ${CPP_SOURCES})

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(laba2 sfml-graphics sfml-audio)
