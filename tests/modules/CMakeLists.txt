function(CreateTestModules NAME)
    add_executable(test_${NAME} ${NAME}.cpp)
    target_link_libraries(test_${NAME} PRIVATE xme_modules)

    target_link_options(test_${NAME} PUBLIC -lc++)
    target_compile_options(test_${NAME} PUBLIC -stdlib=libc++)
    target_compile_options(test_${NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wno-missing-braces)
    target_compile_features(test_${NAME} PUBLIC cxx_std_20)
    add_test(NAME test_${NAME} COMMAND test_${NAME})
endfunction()

CreateTestModules(xme)