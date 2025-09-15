# Geometry library
add_library(geometry
        geometry/Line.cpp
)

target_include_directories(geometry PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

## Scene Library
#add_library(scene
#
#)
#
#target_include_directories(scene PUBLIC
#        ${CMAKE_SOURCE_DIR}/include
#)

#target_link_libraries(scene PUBLIC geometry)

add_executable(quteCAD
        main.cpp
)

target_link_libraries(quteCAD PRIVATE geometry)
