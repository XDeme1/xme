include(CTest)

function(CreateTest NAME)
    add_executable(test_${NAME} ${NAME}.cpp)
    target_link_libraries(test_${NAME} PRIVATE xme)

    target_compile_options(test_${NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wno-missing-braces)
    target_compile_features(test_${NAME} PRIVATE cxx_std_20)
    add_test(NAME test_${NAME} COMMAND test_${NAME})
endfunction()

add_subdirectory(container)
add_subdirectory(math)
add_subdirectory(platform)
add_subdirectory(algorithm)
add_subdirectory(functional)