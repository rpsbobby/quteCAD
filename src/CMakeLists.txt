# Utils
add_library(utils INTERFACE
    utils/common.h
)
target_include_directories(utils INTERFACE
        ${CMAKE_SOURCE_DIR}/src   # so you can do #include "utils/common.h"
)
target_link_libraries(utils INTERFACE Qt5::Core Qt5::Gui Qt5::Widgets)

# Geometry library
add_library(geometry
        geometry/LineEntity.cpp
)

target_link_libraries(geometry PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets utils)
target_include_directories(geometry PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

# Qt Graphics (QtDependent)
add_library(graphics
        graphics/LineItem.cpp
        graphics/LineItem.h
)
target_link_libraries(graphics PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets geometry utils)
target_include_directories(graphics PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

# Main application
add_executable(quteCAD
        main.cpp
)

target_link_libraries(quteCAD PRIVATE geometry graphics)
