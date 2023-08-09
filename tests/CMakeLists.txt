option(XME_TESTS_USE_LIBCXX "Use libc++ to build tests" OFF)

function(CreateTest NAME)
    add_executable(test_${NAME} ${NAME}.cpp)
    target_link_libraries(test_${NAME} PRIVATE xme)
    
    if(XME_TESTS_USE_LIBCXX)
        target_compile_options(test_${NAME} PRIVATE -stdlib=libc++)
        target_link_options(test_${NAME} PRIVATE -lc++)
    endif()
    
    add_test(NAME test_${NAME} COMMAND test_${NAME})
endfunction()

add_subdirectory(math)