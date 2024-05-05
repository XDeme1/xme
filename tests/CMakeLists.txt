option(XME_TESTS_LIBCXX "Use libc++ to test xme" OFF)

if(${XME_TESTS_LIBCXX})
    message(STATUS "Using libc++ to test XME Library")
endif()

find_or_fetch(GTest https://github.com/google/googletest.git main)

function(add_unittest test_name)
    add_executable(${test_name} ${ARGN})
    target_link_libraries(${test_name} PRIVATE xme GTest::gtest_main)
    target_compile_options(${test_name} PRIVATE -march=native -DXME_SIMD_ENABLE_AVX2)
    target_compile_features(${test_name} PRIVATE cxx_std_20)
    gtest_discover_tests(${test_name})
endfunction()

include(GoogleTest)
add_subdirectory(core)
add_subdirectory(container)
add_subdirectory(math)

if(${XME_BUILD_MODULES})
    if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang" AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER_EQUAL "18.0.0")
        add_subdirectory(modules)
    endif()
endif()
