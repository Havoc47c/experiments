cmake_minimum_required(VERSION 3.5)
project(VirtualOverhead)

add_definitions("-std=c++17")
add_definitions("-stdlib=libc++")
add_definitions("-O3")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(bench bench.cpp)
target_link_libraries(bench ${CONAN_LIBS} c++)

add_executable(test test.cpp)
target_link_libraries(test c++)
