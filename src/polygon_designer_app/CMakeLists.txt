cmake_minimum_required (VERSION 3.6)

project(polygon_designer_app)

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(RESOURCES_SRC
	resources.qrc
)

set(MAIN_SRC
	main.cpp
	mainwindow.cpp
	mainwindow.h	
	mainwindow.ui
	drawing_area.h
	drawing_area.cpp
)

set(ALL_SRC
	${RESOURCES_SRC}
	${MAIN_SRC}
)

add_executable(polygon_designer_app ${ALL_SRC} )

target_link_libraries(polygon_designer_app
	polygon_designer_lib
)

qt5_use_modules(polygon_designer_app Core Gui Widgets)

set_target_properties(polygon_designer_app PROPERTIES FOLDER executable)