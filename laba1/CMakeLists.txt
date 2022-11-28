cmake_minimum_required(VERSION 3.22)

project(sfml_test)

set(CMAKE_CXX_STANDARD 17)

file(GLOB CPP_SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${CPP_SOURCES})
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(sfml_test sfml-graphics sfml-audio)