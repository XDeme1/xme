cmake_minimum_required(VERSION 3.26)
project(xme)

set(CMAKE_CXX_EXTENSIONS OFF)

option(XME_BUILD_BENCHMARK "Enables Benchmark" OFF)
option(XME_BUILD_TESTS "Enables Tests" OFF)
option(XME_BUILD_MODULES "Enable modules" OFF)

add_subdirectory(include/xme)

if(${XME_BUILD_MODULES})
    add_subdirectory(modules)
endif()

if(${PROJECT_IS_TOP_LEVEL} OR ${XME_BUILD_TESTS})
    include(CTest)
    add_subdirectory(tests)
endif()

if(${PROJECT_IS_TOP_LEVEL} OR ${XME_BUILD_BENCHMARK})
    add_subdirectory(benchmarks)
endif()
