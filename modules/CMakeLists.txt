add_library(xme_modules)

target_sources(xme_modules PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    math/math.ixx)