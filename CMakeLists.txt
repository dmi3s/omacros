project("mtfind" CXX)

# I run only with cmake 3.22
# You can change the number to an earlier one 
# at your own discretion and at your own risk.
cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 1.80 is the latest version of the boost library at the moment
# An early version possible works too. Or not.
find_package(Boost 1.80 COMPONENTS program_options REQUIRED)


set(OUTPUT_DIR ${CMAKE_BINARY_DIR})

include_directories(
    ${Boost_INCLUDE_DIR},
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

file(GLOB_RECURSE MTFINDER_SRCS
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/*.cpp
    src/*.hpp
)

add_executable("mtfinder" ${MTFINDER_SRCS})
target_sources("mtfinder" PRIVATE ${MTFINDER_SRCS})
TARGET_LINK_LIBRARIES("mtfinder" LINK_PUBLIC ${Boost_LIBRARIES})

# OS specific options

# Haven't tested MSVC. Just copied this lines from old project.
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_WIN32_WINNT=0x0A00) # Target is windows 10
    target_compile_options("ntfinder" PUBLIC "/std:c++latest")
    target_compile_options("ntfinder" PUBLIC "/wd4714")
    target_compile_options("ntfinder" PUBLIC "/W4")
    target_compile_options("ntfinder" PUBLIC "/WX")
    target_compile_options("ntfinder" PUBLIC "/wd4503")
    target_compile_options("ntfinder" PUBLIC "/MP")
    add_compile_options("$<$<CONFIG:RELASE>:/Zi>")
elseif(UNIX)
    find_package(Threads)
    target_link_libraries("mtfinder" ${CMAKE_THREAD_LIBS_INIT})
endif()

# DISABLE WITH:  -DBUILD_TESTS=OFF
option (BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)
    add_subdirectory(${EXT_PROJECTS_DIR}/gtest)       # GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
    include_directories(${GTEST_INCLUDE_DIRS})
    link_directories(${OUTPUT_DIR})
    add_subdirectory(tests)
endif()

