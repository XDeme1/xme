set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
find_or_fetch(benchmark https://github.com/google/benchmark.git main)

# find_or_fetch(glm https://github.com/g-truc/glm.git master)
function(CreateBench NAME)
    add_executable(bench_${NAME} ${NAME}.cpp)
    target_compile_features(bench_${NAME} PRIVATE cxx_std_20)
    target_link_libraries(bench_${NAME} PRIVATE benchmark::benchmark xme)
endfunction()

add_subdirectory(core/functional)
add_subdirectory(container)
add_subdirectory(math)
