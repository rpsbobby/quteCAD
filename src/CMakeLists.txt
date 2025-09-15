# Geometry library
add_library(geometry
        geometry/Line.cpp
)

target_include_directories(geometry PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

add_library(utils INTERFACE)

target_include_directories(utils INTERFACE
        ${CMAKE_SOURCE_DIR}/src   # so you can do #include "utils/common.h"
)

target_link_libraries(utils INTERFACE geometry)
add_executable(quteCAD
        main.cpp
)

target_link_libraries(quteCAD PRIVATE geometry)
