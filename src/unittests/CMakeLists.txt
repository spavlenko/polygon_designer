set(ALL_SRC
	main.cpp
)

source_group("src" FILES ${ALL_SRC})

add_executable(unittests ${ALL_SRC})
target_include_directories (unittests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(unittests
	debug "Debug/gtest_main"
	optimized "Release/gtest_main"
	debug "Debug/gtest"
	optimized "Release/gtest"
	debug "Debug/gmock_main"
	optimized "Release/gmock_main"
	debug "Debug/gmock"
	optimized "Release/gmock"
)
set_target_properties(unittests PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(unittests PROPERTIES FOLDER executable)