cmake_minimum_required(VERSION 3.20...3.28)
project(xme)

set(CMAKE_CXX_EXTENSIONS OFF)

option(XME_BUILD_BENCHMARK "Enables Benchmark" OFF)
option(XME_BUILD_TESTS "Enables Tests" OFF)
option(XME_BUILD_MODULES "Enable modules" OFF)

include(cmake/utils.cmake)

add_library(xme)

target_sources(xme PUBLIC include/xme/core/utility/forward_like.hpp)
set_property(TARGET xme PROPERTY LINKER_LANGUAGE CXX)

target_include_directories(xme PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

if((${XME_BUILD_MODULES}))
    if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang" AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER_EQUAL "18.0.0")
        add_subdirectory(modules)
    endif()
endif()

if(${PROJECT_IS_TOP_LEVEL} OR ${XME_BUILD_TESTS})
    enable_testing()
    add_subdirectory(tests)
endif()

if(${PROJECT_IS_TOP_LEVEL} OR ${XME_BUILD_BENCHMARK})
    add_subdirectory(benchmarks)
endif()
