enable_testing()
#project("mtfind_tests" CXX)

include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB_RECURSE MT_FIND_SRCS_EXECPT_MAIN ${PROJECT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM MT_FIND_SRCS_EXECPT_MAIN ${PROJECT_SOURCE_DIR}/src/main.cpp)

file(GLOB_RECURSE MTFIND_TESTS_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	src/*.cpp
)

list(APPEND MTFIND_TESTS_SRCS ${MT_FIND_SRCS_EXECPT_MAIN})

add_executable(${PROJECT_NAME}_tests ${MTFIND_TESTS_SRCS})

add_dependencies(${PROJECT_NAME}_tests googletest)

target_link_libraries(${PROJECT_NAME}_tests ${GTEST_LIBRARIES} ${Boost_LIBRARIES})
set_target_properties(${PROJECT_NAME}_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

add_custom_command(TARGET ${PROJECT_NAME}_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/data
                ${CMAKE_CURRENT_BINARY_DIR}/data)
 

if(UNIX)
  target_link_libraries (${PROJECT_NAME}_tests ${CMAKE_THREAD_LIBS_INIT})
endif()
