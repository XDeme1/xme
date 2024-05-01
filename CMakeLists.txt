cmake_minimum_required(VERSION 3.20...3.28)
project(xme)

option(XME_BUILD_BENCHMARK "Enables Benchmark" OFF)
option(XME_BUILD_TESTS "Enables Tests" OFF)
option(XME_BUILD_MODULES "Enable modules" OFF)

include(cmake/utils.cmake)

find_or_fetch(ranges-v3 https://github.com/ericniebler/range-v3.git master)

add_library(xme)

target_sources(xme PUBLIC include/xme/core/utility/forward_like.hpp)
set_property(TARGET xme PROPERTY LINKER_LANGUAGE CXX)

target_link_libraries(xme PUBLIC range-v3)
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
