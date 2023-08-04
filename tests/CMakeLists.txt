function(CreateTest NAME)
    add_executable(test_${NAME} ${NAME}.cpp)
    target_link_libraries(test_${NAME} PRIVATE xme)
    
    add_test(NAME test_${NAME} COMMAND test_${NAME})
endfunction()

add_subdirectory(math)