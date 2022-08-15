cmake_minimum_required(VERSION 3.22)
enable_testing()

include_directories(${GTEST_INCLUDE_DIRS})


set(MTFINDER_TESTS_SRCS
	src/main_tests.cpp
	)

add_executable(mtfinder_tests ${MTFINDER_TESTS_SRCS})

add_dependencies(mtfinder_tests googletest)
target_link_libraries(mtfinder_tests ${GTEST_LIBRARIES})
set_target_properties(mtfinder_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})


if(UNIX)
  target_link_libraries (mtfinder_tests ${CMAKE_THREAD_LIBS_INIT})
endif()
