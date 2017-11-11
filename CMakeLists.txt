# Reference: http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html

cmake_minimum_required(VERSION 3.8)

set (CMAKE_PREFIX_PATH "E:\\Development\\libs\\Qt\\5.9.2\\msvc2017_64")

project(polygon_designer LANGUAGES C CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(PROJ_BIN "${PROJECT_SOURCE_DIR}/bin")
set(PROJ_LIB_BIN "${PROJECT_SOURCE_DIR}/lib")
set(PROJ_SRC "${PROJECT_SOURCE_DIR}/src")
set(PROJ_LIBRARIES_SRC "${PROJ_SRC}/libraries")
set(PROJ_EXTERNALS "${PROJECT_SOURCE_DIR}/externals")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJ_LIB_BIN})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJ_LIB_BIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJ_BIN})

set(GOOGLE_TEST_LIB_PATH "${PROJ_EXTERNALS}/googletest/googletest_1.8")
set(OPTIONAL_VALUES_LIB_PATH "${PROJ_EXTERNALS}/optional")

include_directories (
    ${GOOGLE_TEST_LIB_PATH}/include
    ${OPTIONAL_VALUES_LIB_PATH}/include
    ${PROJ_LIBRARIES_SRC}
)

link_directories(
    ${GOOGLE_TEST_LIB_PATH}/binaries
)

message("Configure libraries")
add_subdirectory("${PROJ_LIBRARIES_SRC}/polygon_designer_lib")

message("Configure polygon_designer_app")
add_subdirectory("${PROJ_SRC}/polygon_designer_app")

message("Configure unittests")
add_subdirectory("${PROJ_SRC}/unittests")

