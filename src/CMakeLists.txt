file(GLOB_RECURSE poly_source *.cpp)
add_library(polynoms "${poly_headers}" "${poly_source}")
