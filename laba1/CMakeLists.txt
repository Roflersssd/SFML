cmake_minimum_required(VERSION 3.22)

project(laba1)

set(CMAKE_CXX_STANDARD 17)

file(GLOB CPP_SOURCES "src/*.cpp")


include_directories("${PROJECT_SOURCE_DIR}"/include)

add_executable(${PROJECT_NAME} ${CPP_SOURCES})

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(laba1 sfml-graphics sfml-audio)
