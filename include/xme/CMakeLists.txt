add_library(xme)

target_sources(xme PUBLIC ./core/utility/forward_like.hpp)

target_include_directories(xme PUBLIC ${PROJECT_SOURCE_DIR}/include)
set_property(TARGET xme PROPERTY LINKER_LANGUAGE CXX)
