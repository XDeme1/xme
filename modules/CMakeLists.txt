add_library(xme_modules)

target_sources(xme_modules PUBLIC
    FILE_SET CXX_MODULES TYPE CXX_MODULES FILES
    xme.ixx math/math.ixx)

target_link_libraries(xme_modules PUBLIC xme)
target_compile_features(xme_modules PRIVATE cxx_std_20)