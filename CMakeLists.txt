cmake_minimum_required(VERSION 4.0)
project(quteCAD LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_ASM_STANDARD_REQUIRED ON)

add_subdirectory(src)
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
