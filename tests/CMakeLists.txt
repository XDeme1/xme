option(XME_TESTS_LIBCXX "Use libc++ to test xme" OFF)

if(${XME_TESTS_LIBCXX})
    message(STATUS "Using libc++ to test XME Library")
endif()

find_or_fetch(GTest https://github.com/google/googletest.git main)

function(CreateTest NAME std)
    add_executable(test_${NAME} ${NAME}.cpp)
    target_link_libraries(test_${NAME} PRIVATE xme gtest)

    if(${XME_TESTS_LIBCXX})
        target_compile_options(test_${NAME} PRIVATE -stdlib=libc++)
        target_link_options(test_${NAME} PRIVATE -lc++)
    endif()

    target_compile_options(test_${NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wno-missing-braces)
    target_compile_features(test_${NAME} PRIVATE cxx_std_${std})
    add_test(NAME test_${NAME} COMMAND test_${NAME})
endfunction()

function(add_unittest test_name)
    add_executable(${test_name} ${ARGN})
    target_link_libraries(${test_name} PRIVATE xme GTest::gtest_main)
    target_compile_features(${test_name} PRIVATE cxx_std_23)
endfunction()

add_subdirectory(core)
add_subdirectory(core/functional)
add_subdirectory(core/utility)
add_subdirectory(core/type_traits)
add_subdirectory(container)
add_subdirectory(math)
add_subdirectory(ranges)

if(${PROJECT_IS_TOP_LEVEL} OR ${XME_BUILD_MODULES})
    if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang" AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER_EQUAL "18.0.0")
        add_subdirectory(modules)
    endif()
endif()
