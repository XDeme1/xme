cmake_minimum_required(VERSION 3.26)
project(xme)

option(XME_BUILD_BENCHMARK "Enables Benchmark" OFF)
option(XME_BUILD_TESTS "Enables Tests" OFF)

add_subdirectory(include/xme)

if(${PROJECT_IS_TOP_LEVEL} OR ${XME_BUILD_TESTS})
    include(CTest)
    add_subdirectory(tests)
endif()

if(${PROJECT_IS_TOP_LEVEL} OR ${XME_BUILD_BENCHMARK})
    find_package(benchmark)

    if(${benchmark_FOUND})
        add_subdirectory(benchmarks)
    endif()
endif()