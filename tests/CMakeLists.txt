enable_testing()

include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB_RECURSE MT_FINDER_SRCS_EXECPT_MAIN ${PROJECT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM MT_FINDER_SRCS_EXECPT_MAIN ${PROJECT_SOURCE_DIR}/src/main.cpp)

file(GLOB_RECURSE MTFINDER_TESTS_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	src/*.cpp
)
list(APPEND MTFINDER_TESTS_SRCS ${MT_FINDER_SRCS_EXECPT_MAIN})

add_executable(mtfinder_tests ${MTFINDER_TESTS_SRCS})

add_dependencies(mtfinder_tests googletest)
target_link_libraries(mtfinder_tests ${GTEST_LIBRARIES})
set_target_properties(mtfinder_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})


if(UNIX)
  target_link_libraries (mtfinder_tests ${CMAKE_THREAD_LIBS_INIT})
endif()
