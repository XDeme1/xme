function(CreateBench NAME)
    add_executable(bench_${NAME} ${NAME}.cpp)
    target_compile_features(bench_${NAME} PRIVATE cxx_std_23)
    target_compile_options(bench_${NAME} PRIVATE -mavx -march=native)
    target_link_libraries(bench_${NAME} PRIVATE benchmark::benchmark xme)
endfunction()

CreateBench(vector_operator)