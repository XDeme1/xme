cmake_minimum_required(VERSION 3.26)
project(xme)

option(XME_BUILD_BENCHMARK "Enables Benchmark" OFF)
option(XME_BUILD_TESTS "Enables Tests" OFF)
option(XME_BUILD_MODULES "Enable modules" OFF)

add_subdirectory(include/xme)

if(${PROJECT_IS_TOP_LEVEL} OR ${XME_BUILD_TESTS})
    add_subdirectory(tests)
endif()

if(${PROJECT_IS_TOP_LEVEL} OR ${XME_BUILD_BENCHMARK})
    add_subdirectory(benchmarks)
endif()

if(${XME_BUILD_MODULES})
    add_subdirectory(modules)
endif()