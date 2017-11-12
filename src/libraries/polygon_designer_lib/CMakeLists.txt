cmake_minimum_required (VERSION 3.6)

project(polygon_designer_lib)

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(MAIN_SRC    
    renderer.h
    renderer.cpp
	rendering_strategy.h
	rendering_strategy.cpp
    validator.h
    validator.cpp
	figure.h
    polygon.h
    polygon.cpp
    utils.h
    utils.cpp
    designer.h
    designer.cpp
)

set(ALL_SRC    
    ${MAIN_SRC}
)

add_library(polygon_designer_lib ${ALL_SRC} )

qt5_use_modules(polygon_designer_lib Core Gui Widgets)

set_target_properties(polygon_designer_lib PROPERTIES FOLDER libraries)