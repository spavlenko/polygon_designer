
set(ALL_SRC
    main.cpp
    polygon_utils_tests.cpp
)

source_group("src" FILES ${ALL_SRC})

add_executable(unittests ${ALL_SRC})
target_include_directories (unittests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(unittests
    "gtest_main"    
    "gtest"    
    "gmock_main"    
    "gmock"
    polygon_designer_lib
)

set_target_properties(unittests PROPERTIES FOLDER executable)

