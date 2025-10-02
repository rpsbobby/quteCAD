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

target_link_libraries(geometry PUBLIC utils)
target_include_directories(geometry PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

# Qt Graphics (QtDependent)
add_library(graphics
        graphics/items/LineItem.cpp
        graphics/items/LineItem.h
        graphics/GraphicsView.cpp
        graphics/GraphicsView.h
        graphics/GraphicsScene.cpp
        graphics/GraphicsScene.h
        graphics/items/BaseItem.cpp
        graphics/items/BaseItem.h
        graphics/ItemFactory.cpp
        graphics/ItemFactory.h
        graphics/items/ItemTypes.h
        graphics/items/NodeItem.cpp
        graphics/items/NodeItem.h
        graphics/items/ActiveNode.h
        graphics/items/ActiveNode.cpp
)
target_link_libraries(graphics PUBLIC geometry)
target_include_directories(graphics PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

# Ui Classes
add_library(ui
        ui/mainwindow.cpp
        ui/mainwindow.h
)
target_link_libraries(ui PUBLIC graphics)
target_include_directories(ui PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)
# Main application
add_executable(quteCAD
        main.cpp
)

target_link_libraries(quteCAD PRIVATE ui)
